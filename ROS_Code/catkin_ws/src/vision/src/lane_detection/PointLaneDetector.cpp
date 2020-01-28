#include <vision/lane_detection/PointLaneDetector.hpp>

#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudaarithm.hpp>

#include <opencv2/calib3d.hpp>

#include <iostream>
#include <chrono>
#define _USE_MATH_DEFINES
#include <math.h>
#include <numeric>


using namespace cv;
using namespace cv::cuda;

void drawResult(cv::Mat im, cv::Mat x1, cv::Mat x2, cv::Scalar color, int intersect);


PointLaneDetector::PointLaneDetector(std::map<std::string, std::string>& config) {
	this->vRes = VisionResult();
	this->leftLane1				= cv::Mat::zeros(this->grade, 1, CV_64F);
	this->middleLane1			= cv::Mat::zeros(this->grade, 1, CV_64F);
	this->rightLane1			= cv::Mat::zeros(this->grade, 1, CV_64F);

	this->leftLane2				= cv::Mat::zeros(this->grade, 1, CV_64F);
	this->middleLane2			= cv::Mat::zeros(this->grade, 1, CV_64F);
	this->rightLane2			= cv::Mat::zeros(this->grade, 1, CV_64F);

	this->lA					= cv::Mat::zeros(numberOfLines, grade, CV_64F);
	this->lB					= cv::Mat::zeros(numberOfLines, 1, CV_64F);

	this->mA					= cv::Mat::zeros(numberOfLines, grade, CV_64F);
	this->mB					= cv::Mat::zeros(numberOfLines, 1, CV_64F);

	this->rA					= cv::Mat::zeros(numberOfLines, grade, CV_64F);
	this->rB					= cv::Mat::zeros(numberOfLines, 1, CV_64F);

	this->linePoints 			= cv::Mat::zeros(1, 25, CV_64F);
	this->vRes.detectedPoints.reserve(numberOfLines);
	this->laneMiddles.reserve(25);

	double camera_angle_pitch 	= 	config.count("camera_angle_pitch") 	? stod(config["camera_angle_pitch"]) 	: 17.77;
	double camera_angle_roll 	= 	config.count("camera_angle_roll") 	? stod(config["camera_angle_roll"]) 	: 0.0;
	double camera_angle_yaw 	= 	config.count("camera_angle_yaw") 	? stod(config["camera_angle_yaw"])		: 0.0;
	double camera_focallength 	= 	config.count("camera_focallength") 	? stod(config["camera_focallength"])	: 6.0;
	double camera_height	 	= 	config.count("camera_height") 	 	? stod(config["camera_height"])			: 250.0;
	double camera_res_wid	 	= 	config.count("camera_res_wid") 	 	? stod(config["camera_res_wid"])		: 1600;
	double camera_res_hei	 	= 	config.count("camera_res_hei") 	 	? stod(config["camera_res_hei"])		: 1200;

	double low_thresh		 	= 	config.count("low_thresh") 	 		? stod(config["low_thresh"])			: 50;
	double high_thresh	 		= 	config.count("high_thresh") 	 	? stod(config["high_thresh"])			: 80;
	double aperture_size	 	= 	config.count("aperture_size") 	 	? stod(config["aperture_size"])			: 3;

	this->LANE_THRES_MIN 		= 	config.count("LANE_THRES_MIN") 		? stoi(config["LANE_THRES_MIN"]) 		: 17;
	this->LANE_THRES_MAX 		= 	config.count("LANE_THRES_MAX") 		? stoi(config["LANE_THRES_MAX"]) 		: 0;
	this->LL_MIN_X			 	= 	config.count("LL_MIN_X") 			? stoi(config["LL_MIN_X"])				: 250;
	this->LL_MAX_X 				= 	config.count("LL_MAX_X") 			? stoi(config["LL_MAX_X"])				: 350;
	this->ML_MIN_X	 			= 	config.count("ML_MIN_X") 	 		? stoi(config["ML_MIN_X"])				: 650;
	this->ML_MAX_X	 			= 	config.count("ML_MAX_X") 	 		? stoi(config["ML_MAX_X"])				: 850;
	this->RL_MIN_X	 			= 	config.count("RL_MIN_X") 	 		? stoi(config["RL_MIN_X"])				: 1100;
	this->RL_MAX_X	 			= 	config.count("RL_MAX_X") 	 		? stoi(config["RL_MAX_X"])				: 1300;

	this->canny = cuda::createCannyEdgeDetector(low_thresh, high_thresh, aperture_size, false);

	this->ipmSize = Size(600, 1200);

	/*double alpha_ 			= 90 - camera_angle_pitch;
	double beta_ 			= 90 - camera_angle_roll;
	double gamma_ 			= 90 - camera_angle_yaw;
	double f_ 				= camera_focallength;
	double height 			= camera_height;
	double skew_ 			= 0;
	double pixel_width 		= 7.2;
	double pixel_height 	= 5.4;*/

	double alpha_ = camera_angle_pitch;
	double beta_ = camera_angle_roll;
	double gamma_ = camera_angle_yaw;
	double f_ = camera_focallength;
	double height = camera_height;
	double skew_ = 0;

	double focalLength, dist, alpha, beta, gamma, skew;

	alpha = (alpha_) * M_PI / 180;
	beta = (beta_) * M_PI / 180;
	gamma = (gamma_) * M_PI / 180;
	focalLength = f_;
	dist = height / cos(alpha);
	skew = skew_;

	Size image_size = Size(camera_res_wid, camera_res_hei);
	double w = image_size.width, h = image_size.height;


	// Projecion matrix 2D -> 3D
	Mat A1 = (Mat_<float>(4, 3) <<
		1, 0, -this->ipmSize.width / 2,
		0, 1, -this->ipmSize.height + 205,
		0, 0, 0,
		0, 0, 1);


	// Rotation matrices Rx, Ry, Rz

	Mat RX = (Mat_<float>(4, 4) <<
		1,	0,			0,				0,
		0, 	cos(alpha),	-sin(alpha),	0,
		0, 	sin(alpha),	cos(alpha),		0,
		0, 	0,			0,				1);

	// Change for different y-rotation
	Mat RY = (Mat_<float>(4, 4) <<
		cos(beta), 0, -sin(beta), 0,
		0, 1, 0, 0,
		sin(beta), 0, cos(beta), 0,
		0, 0, 0, 1);

	Mat RZ = (Mat_<float>(4, 4) <<
		cos(gamma), -sin(gamma), 0, 0,
		sin(gamma), cos(gamma), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);


	// R - rotation matrix
	Mat R = RX * RY * RZ;

	// T - translation matrix
	Mat T = (Mat_<float>(4, 4) <<
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, dist,
		0, 0, 0, 1);

	// K - camera matrix, nach: https://en.wikipedia.org/wiki/Camera_resectioning
	Mat K = (Mat_<float>(3, 4) <<
		focalLength*image_size.width	,		skew							,	w / 2	,		0,
		0								,		focalLength*image_size.height	,	h / 2	,		0,
		0								,		0								,	1		,		0);

	K = (Mat_<float>(3, 4) <<
		1786.874566, 0.000000, 707.636847, 0,
		0.000000, 1796.353286, 559.682000, 0,
		0.000000, 0.000000, 1.000000, 0
		);

	this->transformationMat = K * (T * (R * A1));
}

void PointLaneDetector::debugDraw(cv::Mat& frame) {
	cv::cvtColor(frame, this->debugImage, COLOR_GRAY2BGR);
	drawResult(this->debugImage, this->leftLane1, this->leftLane2, Scalar(255, 0, 0), this->intersectionPosL);
	drawResult(this->debugImage, this->middleLane1, this->middleLane2, Scalar(255, 255, 255), this->intersectionPosM);
	drawResult(this->debugImage, this->rightLane1, this->rightLane2, Scalar(0, 0, 255),this->intersectionPosR);

	for (int x = 0; x < this->vRes.lanePoints.size(); x++) {
		for (int y = 0; y < this->vRes.lanePoints.at(x).size(); y++) {
			circle(this->debugImage, this->vRes.lanePoints.at(x).at(y), 5, Scalar(x * 128, 255, 255));
		}
	}
}

double calcX(cv::Mat func, float y) {
	double res = 1/6 * func.at<double>(0,0)*y*y*y + 1/2 * func.at<double>(1,0)*y*y + func.at<double>(2,0)*y + func.at<double>(3,0);
	return res;
}

void drawResult(cv::Mat im, cv::Mat x1, cv::Mat x2, cv::Scalar color, int intersect) {
	for (int row = 0; row < im.rows; row++) {
		cv::Mat column = im.row(row);
		int type = column.type();
		float val = 0;
		if (row > (im.size().height - intersect)) {
			val = calcX(x1, row);
		}
		else {
			val = calcX(x2, row);
		}
		if (val <= im.cols - 1 && val >= 0) {
			circle(im, (cv::Point((int)val, row)), 1, color);
		}
	}
}

//Detectes the driving lanes for one frame
void PointLaneDetector::calculateFrame(cv::Mat& frame) {
	this->doGPUTransform(frame);
	this->calculateAlgorithm();
	//this->debugDraw(this->edge);
}


void PointLaneDetector::doGPUTransform(cv::Mat& frame) {
	this->imageGPU.upload(frame);
	
	cv::cuda::warpPerspective(this->imageGPU, this->ipmGPU, this->transformationMat, this->ipmSize, INTER_CUBIC | WARP_INVERSE_MAP);
	this->ipmGPU.download(this->ipm);
	

	cv::cuda::threshold(this->ipmGPU, this->thresholdGPU, 230, 255, 0);
	this->thresholdGPU.download(this->threshold);

	this->canny->detect(this->ipmGPU, this->edgeGPU);
	this->edgeGPU.download(edge);
}


bool PointLaneDetector::calculateAlgorithm() {
	this->clear();
	stepSize = (this->edge.rows - edgeOffset) / (numberOfLines - 1);
	int lineY = this->edge.rows - 2;											//1: Offset wegen Canny (letzte Zeile schwarz)
	
	this->foundLL = false;
	this->foundML = false;
	this->foundRL = false;

	this->numberOfLeftPoints = 0;
	this->numberOfMiddlePoints = 0;
	this->numberOfRightPoints = 0;

	for (int i = 0; i < this->numberOfLines; i++) {
		cv::findNonZero(this->edge.row(lineY), this->linePoints);
		this->laneMiddlePoints(this->laneMiddles, this->linePoints, lineY);
		this->vRes.detectedPoints.push_back(this->laneMiddles);

		this->prepareInterpolation(i);
		this->classifyPoints(i);

		lineY -= stepSize;
	}
	bool solveRes = this->solveClothoide();
	if (solveRes) {
		
	}
	return solveRes;
}

void PointLaneDetector::clear() {
	this->vRes.lanePoints.at(0).clear();
	this->vRes.lanePoints.at(0).reserve(numberOfLines);
	this->vRes.lanePoints.at(1).clear();
	this->vRes.lanePoints.at(1).reserve(numberOfLines);
	this->vRes.lanePoints.at(2).clear();
	this->vRes.lanePoints.at(2).reserve(numberOfLines);

	this->vRes.detectedPoints.clear();
	this->vRes.detectedPoints.reserve(numberOfLines);

	this->linePoints.release();

	this->laneMiddles.clear();
	this->laneMiddles.reserve(25);
}

void PointLaneDetector::classifyPoints(int line) {
	if (!laneMiddles.empty() && (!foundLL || !foundML || !foundRL)) {
		for (int pointI = 0; pointI < laneMiddles.size(); pointI++) {
			cv::Point analysisPoint = laneMiddles.at(pointI);

			if (analysisPoint.x > LL_MIN_X&& analysisPoint.x < LL_MAX_X) {
				if (!foundLL) {
					foundLL = true;
					leftLaneStartPoint = analysisPoint;
					vRes.lanePoints.at(0).push_back(analysisPoint);
					calculateSolveMatrix(analysisPoint, lA, lB, numberOfLeftPoints);
					laneMiddles.erase(laneMiddles.begin() + pointI);
					//pointI--;
					this->leftDistances[line] = 1;
					numberOfLeftPoints++;
				}
			}
			else if (analysisPoint.x > ML_MIN_X&& analysisPoint.x < ML_MAX_X) {
				if (!foundML) {
					foundML = true;
					middleLaneStartPoint = analysisPoint;
					vRes.lanePoints.at(1).push_back(analysisPoint);
					calculateSolveMatrix(analysisPoint, mA, mB, numberOfMiddlePoints);
					laneMiddles.erase(laneMiddles.begin() + pointI);
					//pointI--;
					this->middleDistances[line] = 1;
					numberOfMiddlePoints++;
				}
			}
			else if (analysisPoint.x > RL_MIN_X&& analysisPoint.x < RL_MAX_X) {
				if (!foundRL) {
					foundRL = true;
					rightLaneStartPoint = analysisPoint;
					vRes.lanePoints.at(2).push_back(analysisPoint);
					calculateSolveMatrix(analysisPoint, rA, rB, numberOfRightPoints);
					laneMiddles.erase(laneMiddles.begin() + pointI);
					//pointI--;
					this->rightDistances[line] = 1;
					numberOfRightPoints++;
				}
			}
		}
	}
}



void PointLaneDetector::prepareInterpolation(int i) {
	if (!laneMiddles.empty() && (foundLL || foundML || foundRL)) {
		std::vector<double> distancesLeft;
		distancesLeft.reserve(laneMiddles.size());

		std::vector<double> distancesMiddle;
		distancesMiddle.reserve(laneMiddles.size());

		std::vector<double> distancesRight;
		distancesRight.reserve(laneMiddles.size());

		std::for_each(laneMiddles.begin(), laneMiddles.end(),
			[this, &distancesLeft, &distancesMiddle, &distancesRight](cv::Point pt) -> void {
				distancesLeft.push_back(cv::norm(pt - this->leftLaneStartPoint));
				distancesMiddle.push_back(cv::norm(pt - this->middleLaneStartPoint));
				distancesRight.push_back(cv::norm(pt - this->rightLaneStartPoint));
			}
		);
		std::vector<double>::iterator iteratorLeft = std::min_element(distancesLeft.begin(), distancesLeft.end());
		int leftIndex = iteratorLeft - distancesLeft.begin();
		std::vector<double>::iterator iteratorMiddle = std::min_element(distancesMiddle.begin(), distancesMiddle.end());
		int middleIndex = iteratorMiddle - distancesMiddle.begin();
		std::vector<double>::iterator iteratorRight = std::min_element(distancesRight.begin(), distancesRight.end());
		int rightIndex = iteratorRight - distancesRight.begin();



		if (leftIndex == middleIndex) {
			if (*iteratorLeft <= *iteratorMiddle) {
				middleIndex = -1;
			}
			else {
				leftIndex = -1;
			}
		}
		if (leftIndex == rightIndex) {
			if (*iteratorLeft <= *iteratorRight) {
				rightIndex = -1;
			}
			else {
				leftIndex = -1;
			}
		}

		if (middleIndex == rightIndex) {
			if (*iteratorMiddle <= *iteratorRight) {
				rightIndex = -1;
			}
			else {
				middleIndex = -1;
			}
		}



		if (foundLL && leftIndex != -1 && distancesLeft.at(leftIndex) < 100) {
			vRes.lanePoints.at(0).push_back(laneMiddles.at(leftIndex));
			calculateSolveMatrix(laneMiddles.at(leftIndex), lA, lB, numberOfLeftPoints - 1);
			leftLaneStartPoint = laneMiddles.at(leftIndex);
			numberOfLeftPoints++;
			
		}
		if (foundML && middleIndex != -1) {
			vRes.lanePoints.at(1).push_back(laneMiddles.at(middleIndex));
			calculateSolveMatrix(laneMiddles.at(middleIndex), mA, mB, numberOfMiddlePoints - 1);
			middleLaneStartPoint = laneMiddles.at(middleIndex);
			numberOfMiddlePoints++;
		}
		if (foundRL && rightIndex != -1 && distancesRight.at(rightIndex) < 100) {
			vRes.lanePoints.at(2).push_back(laneMiddles.at(rightIndex));
			calculateSolveMatrix(laneMiddles.at(rightIndex), rA, rB, numberOfRightPoints - 1);
			rightLaneStartPoint = laneMiddles.at(rightIndex);
			numberOfRightPoints++;
		}
	}
}


bool PointLaneDetector::solveSingleLane(cv::Mat& lane, cv::Mat A, cv::Mat B, int start, int end, bool foundLane) {
	if (!foundLane) {
		return false;
	}
	Range rowRange = Range(start, end);
	Range colRange = Range(0, this->grade);
	Range zeroOneRange = Range(0, 1);
	bool success = cv::solve(A(rowRange, colRange), B(rowRange, zeroOneRange),lane, DECOMP_QR);
	lane.at<double>(0) = lane.at<double>(0) * 6;
	lane.at<double>(1) = lane.at<double>(1) * 2;
	return success;
}

double calculateVariance(cv::Mat& lane,  std::vector<cv::Point> pts) {
	
	std::vector<double> res(pts.size(), 0);
	std::transform(pts.begin(), pts.end(), res.begin(), [lane](cv::Point pt)->double{
		return calcX(lane, pt.y) - pt.x;
	});
	double mean = 0;
	double m2 = 0;
	std::for_each(res.begin(), res.end(), [&mean, &m2](double elem)->void {
		mean+=elem;
		m2+=elem*elem;
	});
	return m2-mean*mean;
	
}

bool PointLaneDetector::solveClothoide() {

	for(int i = 4; i < numberOfLines; i+=5) {
		if (solveSingleLane(this->rightLane1, this->rA, this->rB, 0, i, foundRL)) {
			for (int i = 0; i < this->vRes.lanePoints[0].size(); i++) {
				double variance = calculateVariance(this->rightLane1, this->vRes.lanePoints[2]);
				
			}
		}
	}

	if (foundML && foundRL && numberOfLeftPoints < numberOfRightPoints && numberOfMiddlePoints < numberOfRightPoints) {
		vRes.oppositeLane = false;
	}

	if (foundML && foundRL && !foundLL && numberOfMiddlePoints > numberOfRightPoints) {
		vRes.oppositeLane = true;
	} else {
		vRes.oppositeLane = false;
	}

	bool solveResultL1 = solveSingleLane(this->leftLane1, this->lA, this->lB, 0, numberOfLines - 1, foundLL);
	bool solveResultM1 = solveSingleLane(this->middleLane1, this->mA, this->mB, 0, numberOfLines - 1, foundML);
	bool solveResultR1 = solveSingleLane(this->rightLane1, this->rA, this->rB, 0, numberOfLines - 1, foundRL);

	bool solveResultL2 = solveSingleLane(this->leftLane2, this->lA, this->lB, 0, numberOfLines - 1, foundLL);
	bool solveResultM2 = solveSingleLane(this->middleLane2, this->mA, this->mB, 0, numberOfLines - 1, foundML);
	bool solveResultR2 = solveSingleLane(this->rightLane2, this->rA, this->rB, 0, numberOfLines - 1, foundRL);

	copyResult();
	return solveResultL1 && solveResultM1 && solveResultR1 && solveResultL2 && solveResultM2 && solveResultR2;
}

void mat2Arr(cv::Mat mat, std::array<double, 4>& arr) {
	arr.at(0) = mat.at<double>(0);
	arr.at(1) = mat.at<double>(1);
	arr.at(2) = mat.at<double>(2);
	arr.at(3) = mat.at<double>(3);
}

void PointLaneDetector::copyResult() {
	mat2Arr(this->leftLane1, this->vRes.leftLane1);
	mat2Arr(this->middleLane1, this->vRes.middleLane1);
	mat2Arr(this->rightLane1, this->vRes.rightLane1);
	mat2Arr(this->leftLane2, this->vRes.leftLane2);
	mat2Arr(this->middleLane2, this->vRes.middleLane2);
	mat2Arr(this->rightLane2, this->vRes.rightLane2);
	vRes.foundLL = foundLL;
	vRes.foundML = foundML;
	vRes.foundRL = foundRL;
}

void PointLaneDetector::laneMiddlePoints(std::vector<cv::Point>& laneMiddles, Mat linePoints, int yPos) {
	laneMiddles.clear();
	for (int i = 1; i < linePoints.total(); i++) {
		Point pt1 = linePoints.at<cv::Point>(i - 1);
		Point pt2 = linePoints.at<cv::Point>(i);
		int diff = pt2.x - pt1.x;
		if (diff <= LANE_THRES_MAX && diff >= LANE_THRES_MIN) {
			Point middle;
			middle.x = pt1.x + diff / 2;
			middle.y = pt1.y + (pt2.y - pt1.y) / 2 + yPos;
			laneMiddles.push_back(middle);
		}
	}
}

void PointLaneDetector::calculateSolveMatrix(Point point, cv::Mat& A, cv::Mat& B, int i) {
	A.at<double>(i, 0) = point.y * point.y * point.y;
	A.at<double>(i, 1) = point.y * point.y;
	A.at<double>(i, 2) = point.y;
	A.at<double>(i, 3) = 1;
	B.at<double>(i, 0) = point.x;
}

Mat* halfImage(Mat image) {
	Mat* result = new Mat[2];
	Rect upperHalfSize = Rect(0, 0, image.cols, image.rows / 2);
	result[0] = image(upperHalfSize);

	Rect lowerHalfSize = Rect(0, image.rows / 2, image.cols, image.rows / 2);
	result[1] = image(lowerHalfSize);
	return result;
}
