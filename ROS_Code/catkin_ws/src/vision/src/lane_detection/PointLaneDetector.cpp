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

#define WINDOWS_DEBUG


using namespace cv;
using namespace cv::cuda;

void drawResult(cv::Mat im, cv::Mat x1, cv::Mat x2, cv::Scalar color, int intersect);

void tester(int status, void* userData) {
	std::cout << "TEST";
}

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

	this->thres_cut		 	= 	config.count("thres_cut") 			? stod(config["thres_cut"])				: 127;
	double ipm_correction		 = 	config.count("ipm_correction") 		? stod(config["ipm_correction"])		: 420;

	double low_thresh		 	= 	config.count("canny_low_thresh") 	? stod(config["canny_low_thresh"])			: 50;
	double high_thresh	 		= 	config.count("canny_high_thresh") 	? stod(config["canny_high_thresh"])			: 80;
	double aperture_size	 	= 	config.count("canny_aperture_size") ? stod(config["canny_aperture_size"])			: 3;

	this->LANE_THRES_MIN 		= 	config.count("LANE_THRES_MIN") 		? stoi(config["LANE_THRES_MIN"]) 		: 17;
	this->LANE_THRES_MAX 		= 	config.count("LANE_THRES_MAX") 		? stoi(config["LANE_THRES_MAX"]) 		: 0;
	this->LL_MIN_X			 	= 	config.count("LL_MIN_X") 			? stoi(config["LL_MIN_X"])				: 250;
	this->LL_MAX_X 				= 	config.count("LL_MAX_X") 			? stoi(config["LL_MAX_X"])				: 350;
	this->ML_MIN_X	 			= 	config.count("ML_MIN_X") 	 		? stoi(config["ML_MIN_X"])				: 650;
	this->ML_MAX_X	 			= 	config.count("ML_MAX_X") 	 		? stoi(config["ML_MAX_X"])				: 850;
	this->RL_MIN_X	 			= 	config.count("RL_MIN_X") 	 		? stoi(config["RL_MIN_X"])				: 1100;
	this->RL_MAX_X	 			= 	config.count("RL_MAX_X") 	 		? stoi(config["RL_MAX_X"])				: 1300;

	this->LL_MIN_Y = config.count("LL_MIN_Y") ? stoi(config["LL_MIN_Y"]) : 250;
	this->LL_MAX_Y = config.count("LL_MAX_Y") ? stoi(config["LL_MAX_Y"]) : 350;
	this->ML_MIN_Y = config.count("ML_MIN_Y") ? stoi(config["ML_MIN_Y"]) : 650;
	this->ML_MAX_Y = config.count("ML_MAX_Y") ? stoi(config["ML_MAX_Y"]) : 850;
	this->RL_MIN_Y = config.count("RL_MIN_Y") ? stoi(config["RL_MIN_Y"]) : 1100;
	this->RL_MAX_Y = config.count("RL_MAX_Y") ? stoi(config["RL_MAX_Y"]) : 1300;


	this->ipmScaling			= 	config.count("ipm_scaling") 	 	? stod(config["ipm_scaling"])			: 1;
	this->ipm_size_x			= 	config.count("ipm_size_x") 	 		? stod(config["ipm_size_x"])			: 1200;	
	this->ipm_size_y			= 	config.count("ipm_size_y") 	 		? stod(config["ipm_size_y"])			: 2400;

	this->thresh_mode			=	config.count("thresh_mode")			? stod(config["thresh_mode"])			: 0;
	this->thresh_refresh		=	config.count("thresh_refresh")		? stod(config["thresh_refresh"])			: 100;
	this->thresholdRefreshCounter = this->thresh_refresh;
	this->thresh_otsu_correction=	config.count("thresh_otsu_correction") ? stod(config["thresh_otsu_correction"]) : 50;
	this->thresh_target_percentage = config.count("thresh_target_percentage") ? stod(config["thresh_target_percentage"]) : 0.05;
	this->thresh_target_acc_percentage = config.count("thresh_target_acc_percentage") ? stod(config["thresh_target_acc_percentage"]) : 0.005;

	this->LANE_THRES_MIN 		= 	this->LANE_THRES_MIN 	*  this->ipmScaling;
	this->LANE_THRES_MAX 		= 	this->LANE_THRES_MAX 	*  this->ipmScaling;
	this->LL_MIN_X			 	= 	this->LL_MIN_X 			*  this->ipmScaling;
	this->LL_MAX_X 				= 	this->LL_MAX_X 			*  this->ipmScaling;
	this->ML_MIN_X	 			= 	this->ML_MIN_X 			*  this->ipmScaling;
	this->ML_MAX_X	 			= 	this->ML_MAX_X 			*  this->ipmScaling;
	this->RL_MIN_X	 			= 	this->RL_MIN_X 			*  this->ipmScaling;
	this->RL_MAX_X	 			= 	this->RL_MAX_X 			*  this->ipmScaling;

	this->LL_MIN_Y			 	= 	this->LL_MIN_Y 			*  this->ipmScaling;
	this->LL_MAX_Y 				= 	this->LL_MAX_Y 			*  this->ipmScaling;
	this->ML_MIN_Y	 			= 	this->ML_MIN_Y 			*  this->ipmScaling;
	this->ML_MAX_Y	 			= 	this->ML_MAX_Y 			*  this->ipmScaling;
	this->RL_MIN_Y	 			= 	this->RL_MIN_Y 			*  this->ipmScaling;
	this->RL_MAX_Y	 			= 	this->RL_MAX_Y 			*  this->ipmScaling;

	this->ignoreXMin = (config.count("ignoreXMin") ? stod(config["ignoreXMin"]) : 0) * ipmScaling;
	this->ignoreXMax = (config.count("ignoreXMax") ? stod(config["ignoreXMax"]) : 0)* ipmScaling;
	this->ignoreYMin = (config.count("ignoreYMin") ? stod(config["ignoreYMin"]) : 0)* ipmScaling;
	this->ignoreYMax = (config.count("ignoreYMax") ? stod(config["ignoreYMax"]) : 0)* ipmScaling;


	this->canny = cuda::createCannyEdgeDetector(low_thresh, high_thresh, aperture_size, false);
	this->hough = cuda::createHoughSegmentDetector(1.0f, (float) (CV_PI / 180.0f),50, 5);

	

	this->ipmSize = Size(ipm_size_x * this->ipmScaling, ipm_size_y * this->ipmScaling);

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

	undistort = cv::Mat::zeros(image_size, CV_64F);
	ipm = cv::Mat::zeros(this->ipmSize, CV_64F);
	threshold = cv::Mat::zeros(this->ipmSize, CV_64F);
	edge = cv::Mat::zeros(this->ipmSize, CV_64F);
	debugImage = cv::Mat::zeros(this->ipmSize, CV_64F);


	// Projecion matrix 2D -> 3D
	Mat A1 = (Mat_<float>(4, 3) <<
		1, 0, -this->ipmSize.width / 2,
		0, 1, -this->ipmSize.height + ipm_correction*ipmScaling,
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
		0, 0, 1, dist * this->ipmScaling,
		0, 0, 0, 1);

	cv::Mat K = (Mat_<float>(3, 4) <<
		1786.874566, 0.000000, 707.636847, 0,
		0.000000, 1796.353286, 559.682000, 0,
		0.000000, 0.000000, 1.000000, 0
		);

	this->transformationMat = K * (T * (R * A1));
	
	
	cv::Mat R2 =  (Mat_<float>(3, 3) <<
		1, 0.000000, 0, 
		0.000000, 1, 0, 
		0.000000, 0.000000, 1.000000
		);

	cv::Mat K2 = (Mat_<float>(3, 3) <<
		1786.874566, 0.000000, 707.636847, 
		0.000000, 1796.353286, 559.682000, 
		0.000000, 0.000000, 1.000000
		);

	//cv::Mat distortion = (Mat_<float>(1, 5) << -0.240380403251906, 0.1736768050189452, 0.002374331146303896, 0.001259448491836468, 0);
	//cv::initUndistortRectifyMap(K2, distortion, R2, K2, image_size, CV_32FC1, map1, map2);
	
	#ifdef WINDOWS_DEBUG
	cv::FileStorage storage1("C:\\Users\\Maximilian\\Downloads\\mat1.ext", cv::FileStorage::READ);

	cv::Mat map1;
	storage1["matName1"] >> map1;
	storage1.release();

	cv::FileStorage storage("C:\\Users\\Maximilian\\Downloads\\mat2.ext", cv::FileStorage::READ);

	cv::Mat map2;
	storage["matName1"] >> map2;
	storage.release();

	this->map1GPU.upload(map1);
	this->map2GPU.upload(map2);

	#endif

}

void printLane(cv::Mat& frame, std::array <double, 4> lane, std::string prefix, cv::Point pos) {
	std::string t1 = prefix + " Winkel: " + std::to_string(atan(lane[2]) * 180 / 3.1415) + " Grad";
	std::string t2 = prefix + " Delta: " + std::to_string(lane[3]) + " mm";
	//std::cout << t1 + t2 << std::endl;
	//cv::putText(frame, (t1), pos, cv::FONT_HERSHEY_PLAIN, 3, Scalar(255, 255, 255, 255));
	//cv::putText(frame, (t2), cv::Point(pos.x, pos.y + 100), cv::FONT_HERSHEY_PLAIN, 3, Scalar(255, 255, 255, 255));
}

void PointLaneDetector::debugDraw(cv::Mat& frame) {
	cv::cvtColor(frame, this->debugImage, COLOR_GRAY2BGR);
	
	if (vRes.solvedLL1) {
		printLane(this->debugImage, this->vRes.leftLane1, "Links", cv::Point(100, 100));
		drawResult(this->debugImage, this->leftLane1, this->leftLane2, Scalar(255, 0, 0), this->vRes.clothoideCutDistanceL_mm);
	}

	if (vRes.solvedML1) {
		printLane(this->debugImage, this->vRes.middleLane1, "Mitte", cv::Point(100, 300));
		drawResult(this->debugImage, this->middleLane1, this->middleLane2, Scalar(255, 255, 255), this->vRes.clothoideCutDistanceM_mm);
	}

	if (vRes.solvedRL1) {
		printLane(this->debugImage, this->vRes.rightLane1, "Rechts", cv::Point(100, 500));
		drawResult(this->debugImage, this->rightLane1, this->rightLane2, Scalar(0, 0, 255), this->vRes.clothoideCutDistanceR_mm);
	}


	
	
	
	

	for (int x = 0; x < this->vRes.lanePoints.size(); x++) {
		for (int y = 0; y < this->vRes.lanePoints.at(x).size(); y++) {
			
			circle(this->debugImage, this->vRes.lanePoints.at(x).at(y), 5, Scalar(x * 128, 255, 255));
		}
	}
}

double calcX(cv::Mat func, double y) {
	double d1 = func.at<double>(0, 0) / 6;
	double d2 = d1 * y;
	double d3 = d2 * y;
	double d4 = d3 * y;

	double z1 = func.at<double>(1, 0) / 2;
	double z2 = z1 * y;
	double z3 = z2 * y;

	double e1 = func.at<double>(2, 0);
	double e2 = e1 * y;

	double n1 = func.at<double>(3, 0);

	double ergebnis = d4 + z3 + e2 + n1;

	return ergebnis;
}

void PointLaneDetector::drawResult(cv::Mat im, cv::Mat x1, cv::Mat x2, cv::Scalar color, double intersect) {
	for (int row = im.rows - 1; row >= 0 ; row--) {
		float val = 0;
		int tY = imToReY(row + 1);
		int tX = 0;
		if (tY <= intersect) {
			val = calcX(x1, tY);
		}
		else {
			val = calcX(x2, tY);
		}
		tX = reToImX(val);
		if (tX <= im.cols - 1 && tX >= 0) {
			circle(im, (cv::Point(tX, row)), 1, color);
		}
	}
}

//Detectes the driving lanes for one frame
void PointLaneDetector::calculateFrame(cv::Mat& frame) {
	if (!frame.empty()) {
		this->doGPUTransform(frame);
		this->calculateAlgorithm();
		this->debugDraw(this->edge);
	}
}


void PointLaneDetector::doGPUTransform(cv::Mat& frame) {
	this->imageGPU.upload(frame);

	cv::cuda::remap(this->imageGPU, this->undistortGPU, this->map1GPU, this->map2GPU, cv::INTER_NEAREST, cv::BORDER_CONSTANT, std::numeric_limits<float>::quiet_NaN());
	this->undistortGPU.download(this->undistort);	

	cv::cuda::warpPerspective(this->undistortGPU, this->ipmGPU, this->transformationMat, this->ipmSize, INTER_CUBIC | WARP_INVERSE_MAP);
	this->ipmGPU.download(this->ipm);
	

	switch (this->thresh_mode)
	{
	case 0:
		cv::cuda::threshold(this->ipmGPU, this->thresholdGPU, this->thres_cut, 255, cv::THRESH_BINARY);
		this->thresholdGPU.download(this->threshold);
		break;

	case 1:
		if (thresholdRefreshCounter >= this->thresh_refresh) {
			this->thres_cut = cv::threshold(ipm, this->threshold, 0, 255, THRESH_OTSU) + 50;
			this->thresholdGPU.upload(this->threshold);
			std::cout << "Recalculating...";
			thresholdRefreshCounter = 0;
		}
		else {
			cv::cuda::threshold(this->ipmGPU, this->thresholdGPU, this->thres_cut, 255, cv::THRESH_BINARY);
			this->thresholdGPU.download(this->threshold);
		}
		thresholdRefreshCounter++;
		break;
	case 2:
		if (thresholdRefreshCounter >= this->thresh_refresh) {
			this->calculateThreshold(frame);
			thresholdRefreshCounter = 0;
		}
		else {
			cv::cuda::threshold(this->ipmGPU, this->thresholdGPU, this->thres_cut-this->thresh_otsu_correction, 255, cv::THRESH_BINARY);
			this->thresholdGPU.download(this->threshold);
		}
		thresholdRefreshCounter++;
		break;
	default:
		cv::cuda::threshold(this->ipmGPU, this->thresholdGPU, this->thres_cut, 255, cv::THRESH_BINARY);
		this->thresholdGPU.download(this->threshold);
		break;
	}



	this->canny->detect(this->thresholdGPU, this->edgeGPU);
	this->edgeGPU.download(edge);

	//Hough Transformation 
	houghZumutung.lock();
	this->hough->detect(this->edgeGPU, this->houghLinesGPU, stream);
	this->stream.enqueueHostCallback(&PointLaneDetector::houghStreamCb, this);
	houghZumutung.unlock();
}

void PointLaneDetector::houghStreamCb(int status, void *userData) {
	PointLaneDetector *self = static_cast<PointLaneDetector *>(userData);
	std::lock_guard<std::mutex> lk(self->houghMutex);
	self->condition.notify_one();
}

void PointLaneDetector::calculateAlgorithm() {
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
	this->solveClothoide();
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

	leftIndex = -1;
	middleIndex = -1;
	rightIndex = -1;

	oldLeftRel = -1;
	oldMiddleRel = -1;
	oldRIghtRel = -1;
}

void PointLaneDetector::calculateThreshold(cv::Mat & frame)
{
		cv::cuda::GpuMat thresholdTest;
		int thres = 128;
		double comp = 0.0;
		double dest = this->thresh_target_percentage;
		int i = 0;
		do {
			cv::cuda::threshold(ipmGPU, thresholdTest, thres, 255, THRESH_BINARY);
			double nonZero = cv::cuda::countNonZero(thresholdTest);
			comp = nonZero / ((double)this->ipm_size_x * (double)this->ipm_size_y);
			if (comp < dest) {
				thres = thres - 500 * abs(comp-dest);
				if (thres <= 30) {
					thres = 30;
					break;
				}
			}
			else {
				thres = thres + 500 * abs(comp - dest);
				if (thres >= 225) {
					thres = 225;
					break;
				}
			}
			i++;
			if (i > 20) {
				break;
			}
		} while (abs(comp - dest) >= this->thresh_target_acc_percentage);
		this->thres_cut = thres;
		this->thresholdGPU = thresholdTest;
		this->thresholdGPU.download(this->threshold);
}

double PointLaneDetector::imToReX(int x)
{
	return ((double)x - ipmSize.width / 2);
}

int PointLaneDetector::reToImX(double x)
{
	return (int)(x + this->ipmSize.width / 2);
}

double PointLaneDetector::imToReY(int y)
{
	return (-(double)y + ipmSize.height);
}

int PointLaneDetector::reToImY(double y)
{
	return (int)(-y + this->ipmSize.height);
}

void PointLaneDetector::classifyPoints(int line) {
	if (!laneMiddles.empty() && (!foundLL || !foundML || !foundRL)) {
		for (int pointI = 0; pointI < laneMiddles.size(); pointI++) {
			cv::Point analysisPoint = laneMiddles.at(pointI);
			if (pointI == leftIndex || pointI == middleIndex || pointI == rightIndex) {
				continue;
			}

			if (analysisPoint.x > LL_MIN_X&& analysisPoint.x < LL_MAX_X && analysisPoint.y >= LL_MIN_Y && analysisPoint.y < LL_MAX_Y) {
				if (!foundLL) {
					foundLL = true;
					leftLaneStartPoint = analysisPoint;
					vRes.lanePoints.at(0).push_back(analysisPoint);
					calculateSolveMatrix(analysisPoint, lA, lB, numberOfLeftPoints);
					laneMiddles.erase(laneMiddles.begin() + pointI);
					this->leftDistances[line] = 1;
					lastLeftIterator = line;
					numberOfLeftPoints++;
				}
			}
			else if (analysisPoint.x > ML_MIN_X&& analysisPoint.x < ML_MAX_X && analysisPoint.y >= ML_MIN_Y && analysisPoint.y < ML_MAX_Y) {
				if (!foundML) {
					foundML = true;
					middleLaneStartPoint = analysisPoint;
					vRes.lanePoints.at(1).push_back(analysisPoint);
					calculateSolveMatrix(analysisPoint, mA, mB, numberOfMiddlePoints);
					laneMiddles.erase(laneMiddles.begin() + pointI);
					this->middleDistances[line] = 1;
					lastMiddleIterator = line;
					numberOfMiddlePoints++;
				}
			}
			else if (analysisPoint.x > RL_MIN_X&& analysisPoint.x < RL_MAX_X && analysisPoint.y >= RL_MIN_Y && analysisPoint.y < RL_MAX_Y) {
				if (!foundRL) {
					foundRL = true;
					rightLaneStartPoint = analysisPoint;
					vRes.lanePoints.at(2).push_back(analysisPoint);
					calculateSolveMatrix(analysisPoint, rA, rB, numberOfRightPoints);
					laneMiddles.erase(laneMiddles.begin() + pointI);
					this->rightDistances[line] = 1;
					lastRightIterator = line;
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
		this->leftIndex = iteratorLeft - distancesLeft.begin();
		std::vector<double>::iterator iteratorMiddle = std::min_element(distancesMiddle.begin(), distancesMiddle.end());
		this->middleIndex = iteratorMiddle - distancesMiddle.begin();
		std::vector<double>::iterator iteratorRight = std::min_element(distancesRight.begin(), distancesRight.end());
		this->rightIndex = iteratorRight - distancesRight.begin();



		if (foundLL && foundML && leftIndex == middleIndex) {
			if (*iteratorLeft <= *iteratorMiddle) {
				middleIndex = -1;
			}
			else {
				leftIndex = -1;
			}
		}
		if (foundLL && foundRL && leftIndex == rightIndex) {
			if (*iteratorLeft <= *iteratorRight) {
				rightIndex = -1;
			}
			else {
				leftIndex = -1;
			}
		}

		if (foundML && foundRL && middleIndex == rightIndex) {
			if (*iteratorMiddle <= *iteratorRight) {
				rightIndex = -1;
			}
			else {
				middleIndex = -1;
			}
		}

		



		if (foundLL && leftIndex >= 0 && distancesLeft.at(leftIndex) < 420) {
			int dx = laneMiddles.at(leftIndex).x - this->leftLaneStartPoint.x;
			int dy = laneMiddles.at(leftIndex).y - this->leftLaneStartPoint.y;
			double temp = (double)i - (double)lastLeftIterator;
			double rel = abs(oldLeftRel - (dx / dy));
			if (oldLeftRel < 0 || rel < 0.3) {
				lastLeftIterator = i;
				vRes.lanePoints.at(0).push_back(laneMiddles.at(leftIndex));
				calculateSolveMatrix(laneMiddles.at(leftIndex), lA, lB, numberOfLeftPoints);
				leftLaneStartPoint = laneMiddles.at(leftIndex);
				oldLeftRel = (dx / dy);
				numberOfLeftPoints++;
			}			
		}
		else {
			leftIndex = -1;
		}

		if (foundML && middleIndex >= 0) {
			double dx = ((double)laneMiddles.at(middleIndex).x - (double)this->middleLaneStartPoint.x);
			double dy = ((double)laneMiddles.at(middleIndex).y - (double)this->middleLaneStartPoint.y);
			double rel = oldMiddleRel - (dx / dy);
			if ((*iteratorMiddle < 400 && numberOfMiddlePoints == 1) || (*iteratorMiddle < 300 && rel < 0.5 && rel > -0.5) || (*iteratorMiddle >= 300 && rel < 0.1 && rel > -0.1)) {
				lastMiddleIterator = i;
				vRes.lanePoints.at(1).push_back(laneMiddles.at(middleIndex));
				calculateSolveMatrix(laneMiddles.at(middleIndex), mA, mB, numberOfMiddlePoints);
				middleLaneStartPoint = laneMiddles.at(middleIndex);
				
				numberOfMiddlePoints++;
				oldMiddleRel = (dx / dy);
				
			}
		}
		else {
			middleIndex = -1;
		}
		if (foundRL && rightIndex >= 0) {
			double dx = ((double)laneMiddles.at(rightIndex).x - (double)this->rightLaneStartPoint.x);
			double dy = ((double)laneMiddles.at(rightIndex).y - (double)this->rightLaneStartPoint.y);
			double rel = oldRIghtRel - (dx / dy);
			if ((*iteratorRight < 300 && numberOfRightPoints == 1) || (*iteratorRight < 300 && rel < 0.2 && rel > -0.2) || (*iteratorRight >= 300 && rel < 0.1 && rel > -0.1)) {
				lastRightIterator = i;
				vRes.lanePoints.at(2).push_back(laneMiddles.at(rightIndex));
				calculateSolveMatrix(laneMiddles.at(rightIndex), rA, rB, numberOfRightPoints);
				rightLaneStartPoint = laneMiddles.at(rightIndex);
				oldRIghtRel = (dx / dy);
				numberOfRightPoints++;
			}
		}
		else {
			rightIndex = -1;
		}
	}
}

bool PointLaneDetector::solveSingleLane(cv::Mat& lane, cv::Mat A, cv::Mat B, int start, int end, bool foundLane) {
	if (!foundLane || end - start < grade || end-start < 8) {
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

double PointLaneDetector::calculateVariance(cv::Mat& lane,  std::vector<cv::Point> pts) {
	std::vector<double> res(pts.size(), 0);
	std::transform(pts.begin(), pts.end(), res.begin(), [this, lane](cv::Point point)->double{
		point.y = imToReY(point.y);
		point.x = imToReX(point.x);
		return calcX(lane, point.y) - point.x;
	});
	double mean = 0;
	double m2 = 0;
	std::for_each(res.begin(), res.end(), [&mean, &m2](double elem)->void {
		mean+=elem;
		m2+=elem*elem;
	});
	return m2 - mean * mean;
	
}

void PointLaneDetector::solveClothoide() {
	int separationIndexL = 0;
	int separationIndexM = 0;
	int separationIndexR = 0;

	int separationDist = 0;
	/*for(int i = 4; i < numberOfRightPoints && separationIndexR == 0; i+=5) {
		
		if (solveSingleLane(this->rightLane1, this->rA, this->rB, 0, i, foundRL)) {
			double variance = calculateVariance(this->rightLane1, this->vRes.lanePoints[2]);
			//std::cout << variance;
			if (variance > 10) {
				separationIndexR = i;
				separationDist = this->vRes.lanePoints[2].at(separationIndexR).y;
			}
			
		}
	}
	this->vRes.clothoideCutDistanceR_mm = imToReY(separationDist);*/
	

	//Keine Trennung gefunden -> nur C1 ist valide
	separationIndexR = 0;
	if(separationIndexR == 0) {
		separationIndexL = numberOfLeftPoints;
		separationIndexM = numberOfMiddlePoints;
		separationIndexR = numberOfRightPoints;

		this->vRes.clothoideCutDistanceL_mm = imToReY(0);
		this->vRes.clothoideCutDistanceM_mm = imToReY(0);
		this->vRes.clothoideCutDistanceR_mm = imToReY(0);
	} else {
		if(foundLL) {
			auto res = std::find_if(this->vRes.lanePoints[0].begin(), this->vRes.lanePoints[0].end(), [&separationDist](cv::Point& elem) -> bool {
				return elem.y > separationDist;
			});
			this->vRes.clothoideCutDistanceL_mm = imToReY((*res).y);
			separationIndexL = res - this->vRes.lanePoints[0].begin();
		}
		if(foundML) {
			auto res = std::find_if(this->vRes.lanePoints[1].begin(), this->vRes.lanePoints[1].end(), [&separationDist](cv::Point& elem) -> bool {
				return elem.y > separationDist;
			});
			this->vRes.clothoideCutDistanceM_mm = imToReY((*res).y);
			separationIndexM = res - this->vRes.lanePoints[1].begin();
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

	
	this->vRes.solvedLL1 = solveSingleLane(this->leftLane1, this->lA, this->lB, 0, separationIndexL, foundLL);
	this->vRes.solvedML1 = solveSingleLane(this->middleLane1, this->mA, this->mB, 0, separationIndexM, foundML);
	this->vRes.solvedRL1 = solveSingleLane(this->rightLane1, this->rA, this->rB, 0, separationIndexR, foundRL);

	//std::cout << this->leftLane1;


	//this->vRes.solvedLL2 = solveSingleLane(this->leftLane2, this->lA, this->lB, separationIndexL, numberOfLines, foundLL);
	//this->vRes.solvedML2 = solveSingleLane(this->middleLane2, this->mA, this->mB, separationIndexM, numberOfLines, foundML);
	//this->vRes.solvedRL2 = solveSingleLane(this->rightLane2, this->rA, this->rB, separationIndexR, numberOfLines, foundRL);
	
	//std::cout << this->leftLane2;
	copyResult();
}

void PointLaneDetector::mat2Arr(cv::Mat& mat, std::array<double, 4>& arr) {
	arr.at(0) = mat.at<double>(0) * ipmScaling * ipmScaling;
	arr.at(1) = mat.at<double>(1) * ipmScaling;
	arr.at(2) = mat.at<double>(2);
	arr.at(3) = mat.at<double>(3) / ipmScaling;
}

void PointLaneDetector::copyResult() {
	//if (!this->vRes.oppositeLane) {
		mat2Arr(this->leftLane1, this->vRes.leftLane1);
		mat2Arr(this->middleLane1, this->vRes.middleLane1);
		mat2Arr(this->rightLane1, this->vRes.rightLane1);
		mat2Arr(this->leftLane2, this->vRes.leftLane2);
		mat2Arr(this->middleLane2, this->vRes.middleLane2);
		mat2Arr(this->rightLane2, this->vRes.rightLane2);
		vRes.foundLL = foundLL;
		vRes.foundML = foundML;
		vRes.foundRL = foundRL;
	/*} else {
		mat2Arr(this->middleLane1, this->vRes.leftLane1);
		mat2Arr(this->rightLane1, this->vRes.middleLane1);

		mat2Arr(this->middleLane1, this->vRes.leftLane1);
		mat2Arr(this->rightLane1, this->vRes.middleLane1);

		vRes.foundLL = foundML;
		vRes.foundML = foundRL;
		vRes.foundRL = false;

		vRes.solvedLL1 = vRes.solvedML1;
		vRes.solvedML1 = vRes.solvedRL1;
		vRes.solvedRL1 = false;
	
		vRes.solvedLL2 = vRes.solvedML2;
		vRes.solvedML2 = vRes.solvedRL2;
		vRes.solvedRL2 = false;
	}*/
	
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
			if (!(middle.x > ignoreXMin && middle.x <= ignoreXMax && middle.y > ignoreYMin&& middle.y <= ignoreYMax)) {
				laneMiddles.push_back(middle);
			} 
		}
	}
}

void PointLaneDetector::calculateSolveMatrix(Point point, cv::Mat& A, cv::Mat& B, int i) {
	point.y = imToReY(point.y);
	point.x = imToReX(point.x);

	A.at<double>(i, 0) = (double)point.y * (double)point.y * (double)point.y;
	A.at<double>(i, 1) = (double)point.y * (double)point.y;
	A.at<double>(i, 2) = point.y;
	A.at<double>(i, 3) = 1;
	B.at<double>(i, 0) = point.x;
}
