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


PointLaneDetector::PointLaneDetector() {

	this->leftLane1 = cv::Mat::zeros(this->grade, 1, CV_64F);
	this->middleLane1 = cv::Mat::zeros(this->grade, 1, CV_64F);
	this->rightLane1 = cv::Mat::zeros(this->grade, 1, CV_64F);

	this->leftLane2 = cv::Mat::zeros(this->grade, 1, CV_64F);
	this->middleLane2 = cv::Mat::zeros(this->grade, 1, CV_64F);
	this->rightLane2 = cv::Mat::zeros(this->grade, 1, CV_64F);

	this->lA = cv::Mat::zeros(numberOfLines, grade, CV_64F);
	this->lB = cv::Mat::zeros(numberOfLines, 1, CV_64F);

	this->mA = cv::Mat::zeros(numberOfLines, grade, CV_64F);
	this->mB = cv::Mat::zeros(numberOfLines, 1, CV_64F);

	this->rA = cv::Mat::zeros(numberOfLines, grade, CV_64F);
	this->rB = cv::Mat::zeros(numberOfLines, 1, CV_64F);

	this->detectedPoints.reserve(numberOfLines);

	linePoints = cv::Mat::zeros(1, 25, CV_64F);

	this->laneMiddles.reserve(25);

	this->canny = cuda::createCannyEdgeDetector(900, 50, 3);

	int alpha_ = 60, beta_ = 90, gamma_ = 90;
	double f_ = 300, dist_ = 200, skew_ = 0;             //skew ist Schraeglageparameter (dreht das Bild nach Rechts oder Links) ->Vollstaendigkeit
	double pixel_width = 7.2;
	double pixel_height = 5.4;

	//TODO: dist_ aendern
	//dist_ = 82;

	double focalLength, dist, alpha, beta, gamma, skew;

	alpha = ((double)alpha_ - 90) * M_PI / 180;
	beta = ((double)beta_ - 90) * M_PI / 180;
	gamma = ((double)gamma_ - 90) * M_PI / 180;
	focalLength = (double)f_;

	//TODO: dist ist eigentlich: dist = (KamH�he/sin((180-KameraWinkel)))
	dist = (double)dist_;
	skew = skew_;

	Size image_size = Size(1600, 1200);
	double w = (double)image_size.width, h = (double)image_size.height;


	// Projecion matrix 2D -> 3D
	Mat A1 = (Mat_<float>(4, 3) <<
		1, 0, -w / 2,
		0, 1, -h / 2,
		0, 0, 0,
		0, 0, 1);


	// Rotation matrices Rx, Ry, Rz

	Mat RX = (Mat_<float>(4, 4) <<
		1, 0, 0, 0,
		0, cos(alpha), -sin(alpha), 0,
		0, sin(alpha), cos(alpha), 0,
		0, 0, 0, 1);

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

	// K - camera matrix
	Mat K = (Mat_<float>(3, 4) <<
		focalLength * pixel_width	,		skew,						w / 2,		0,
		0							,		focalLength * pixel_height,	h / 2,		0,
		0							,		0,							1,			0
		);
	this->transformationMat = K * (T * (R * A1));
}

#define LANE_THRES_MIN 5
#define LANE_THRES_MAX 60
#define LL_MIN_X	670
#define LL_MAX_X	730
#define ML_MIN_X	780
#define ML_MAX_X	820
#define RL_MIN_X	880
#define RL_MAX_X	930


void PointLaneDetector::debugDraw(cv::Mat& frame) {
	cv::cvtColor(frame, frame, COLOR_GRAY2BGR);
	drawResult(frame, this->leftLane1, this->leftLane2, Scalar(255, 0, 0), this->intersectionPosL);
	drawResult(frame, this->middleLane1, this->middleLane2, Scalar(255, 255, 255), this->intersectionPosM);
	drawResult(frame, this->rightLane1, this->rightLane2, Scalar(0, 0, 255),this->intersectionPosR);


	for (int x = 0; x < this->result.size(); x++) {
		for (int y = 0; y < this->result.at(x).size(); y++) {
			circle(frame, this->result.at(x).at(y), 5, Scalar(x * 128, 255, 255));
		}
	}
	cv::resize(frame, frame, Size(800, 600));
	imshow("Result image", frame);

}

double calcX(cv::Mat func, float y) {
	double res = 0;
	for (int i = 0; i < func.rows; i++) {
		double num = func.at<double>(i, 0);
		res = res + num * pow(y, func.rows - 1 - i);
	}
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

VisionResult PointLaneDetector::getResult() {
	return VisionResult();
}

//Detectes the driving lanes for one frame
void PointLaneDetector::calculateFrame(cv::Mat& frame) {
	cv::Mat edgeImage;
	cv::Mat binaryImage;
	//imshow("~/Desktop/test.png", frame);
	auto timeStart = std::chrono::high_resolution_clock::now();
	this->doGPUTransform(frame,edgeImage, binaryImage);
	this->calculateAlgorithm(edgeImage, 0);
	auto timeEnd = std::chrono::high_resolution_clock::now();
	//imshow("edge", edgeImage);
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
	//std::cout << "\033[2J\033[1;1H";
	std::cout <<"Dauer: " << duration << std::endl;
	
	//this->debugDraw(edgeImage);
	waitKey(1);
}

void PointLaneDetector::clear() {
	this->result.at(0).clear();
	this->result.at(0).reserve(numberOfLines);
	this->result.at(1).clear();
	this->result.at(1).reserve(numberOfLines);
	this->result.at(2).clear();
	this->result.at(2).reserve(numberOfLines);

	this->detectedPoints.clear();
	this->detectedPoints.reserve(numberOfLines);

	this->linePoints.release();

	this->laneMiddles.clear();
	this->laneMiddles.reserve(25);
}



bool PointLaneDetector::calculateAlgorithm(cv::Mat& frame, int startLine)
{
	this->clear();
	stepSize = (frame.rows - edgeOffset) / (numberOfLines - 1);
	int lineY = frame.rows - 2 - stepSize * startLine;											//1: Offset wegen Canny (letzte Zeile schwarz)

	
	this->foundLL = false;
	this->foundML = false;
	this->foundRL = false;

	this->numberOfLeftPoints = 0;
	this->numberOfMiddlePoints = 0;
	this->numberOfRightPoints = 0;

	for (int i = 0; i < this->numberOfLines; i++) {
		cv::findNonZero(frame.row(lineY), this->linePoints);
		this->laneMiddlePoints(this->laneMiddles, this->linePoints, lineY);
		this->detectedPoints.push_back(this->laneMiddles);

		this->classifyPoints(i);
		this->prepareInterpolation(i);

		lineY -= stepSize;
	}
	bool solveRes = this->solveClothoide();
	return solveRes;
}

/*

cv::Mat PointLaneDetector::doGPUTransform(cv::Mat& frame) {
	cv::cuda::GpuMat upload(frame);
	cv::cuda::GpuMat binary;
	cv::cuda::threshold(upload, binary, 128, 255, THRESH_BINARY);
	cv::cuda::GpuMat ipm;
	cv::cuda::warpPerspective(binary, ipm,this->transformationMat, frame.size(), INTER_CUBIC | WARP_INVERSE_MAP);
	canny->detect(ipm, upload);
	Mat edgeImage(upload);
	frame = edgeImage;
	return Mat(binary);
}*/


void PointLaneDetector::doGPUTransform(cv::Mat frame, cv::Mat& edgeImage, cv::Mat& binaryImage) {
	cv::cuda::GpuMat upload(frame);
	cv::cuda::GpuMat ipm;
	cv::cuda::GpuMat binary;
	cv::cuda::GpuMat edge;

	cv::cuda::warpPerspective(upload, ipm, this->transformationMat, frame.size(), INTER_CUBIC | WARP_INVERSE_MAP);
	cv::Mat test(ipm);
	cv::resize(test, test, Size(800, 600));
	//imshow("tester", test);

		cv::cuda::threshold(ipm, binary, 128, 255, THRESH_BINARY);
		binary.download(binaryImage);
		this->canny->detect(ipm, edge);
		edge.download(edgeImage);
	}


/*void PointLaneDetector::doGPUTransform(cv::Mat frame, cv::Mat& edgeImage, cv::Mat& binaryImage) {
	cv::cuda::GpuMat upload(frame);
	cv::cuda::GpuMat ipm;
	cv::cuda::GpuMat binary;
	cv::cuda::GpuMat edge;

	cv::cuda::warpPerspective(upload, ipm, this->transformationMat, frame.size(), INTER_CUBIC | WARP_INVERSE_MAP);

	cv::cuda::threshold(ipm, binary, 128, 255, THRESH_BINARY);
	binary.download(binaryImage);
	this->canny->detect(ipm, edge);
	edge.download(edgeImage);

}*/

void PointLaneDetector::classifyPoints(int line) {
	if (!laneMiddles.empty() && (!foundLL || !foundML || !foundRL)) {
		for (int pointI = 0; pointI < laneMiddles.size(); pointI++) {
			cv::Point analysisPoint = laneMiddles.at(pointI);

			if (analysisPoint.x > LL_MIN_X&& analysisPoint.x < LL_MAX_X) {
				if (!foundLL) {
					foundLL = true;
					leftLaneStartPoint = analysisPoint;
					result.at(0).push_back(analysisPoint);
					calculateSolveMatrix(analysisPoint, lA, lB, numberOfLeftPoints);
					laneMiddles.erase(laneMiddles.begin() + pointI);
					pointI--;
					this->leftDistances[line] = 1;
					numberOfLeftPoints++;
				}
			}
			else if (analysisPoint.x > ML_MIN_X&& analysisPoint.x < ML_MAX_X) {
				if (!foundML) {
					foundML = true;
					middleLaneStartPoint = analysisPoint;
					result.at(1).push_back(analysisPoint);
					calculateSolveMatrix(analysisPoint, mA, mB, numberOfMiddlePoints);
					laneMiddles.erase(laneMiddles.begin() + pointI);
					pointI--;
					this->middleDistances[line] = 1;
					numberOfMiddlePoints++;
				}
			}
			else if (analysisPoint.x > RL_MIN_X&& analysisPoint.x < RL_MAX_X) {
				if (!foundRL) {
					foundRL = true;
					rightLaneStartPoint = analysisPoint;
					result.at(2).push_back(analysisPoint);
					calculateSolveMatrix(analysisPoint, rA, rB, numberOfRightPoints);
					laneMiddles.erase(laneMiddles.begin() + pointI);
					pointI--;
					this->rightDistances[line] = 1;
					numberOfRightPoints++;
				}
			}
		}
	}
}

void PointLaneDetector::doMean(std::array<double, numberOfLines>& arr) {
	int counter = 0;
	std::for_each(arr.begin(), arr.end(), [this, &counter, &arr](double element) -> void {
		if (element == 0) {
			int i = 1;
			double itElement = 0;
			do {
				if (i + counter >= numberOfLines) {
					return;
				}
				itElement = arr.at(counter + i);
				if (itElement != 0) {
					std::fill(arr.begin() + counter, arr.begin() + counter + i + 1, itElement / (i+1));
				}
				i++;
			} while (itElement == 0);
		}
		counter++;
	});
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



		if (foundLL ) {
			if (leftIndex != -1 && distancesLeft.at(leftIndex) < 100) {
				result.at(0).push_back(laneMiddles.at(leftIndex));
				calculateSolveMatrix(laneMiddles.at(leftIndex), lA, lB, numberOfLeftPoints);
				leftLaneStartPoint = laneMiddles.at(leftIndex);
				this->leftDistances.at(i - 1) = distancesLeft.at(leftIndex);
				this->leftLineIndices.at(i) = numberOfLeftPoints;
				numberOfLeftPoints++;
			}
			else {
				
			}
		}
		if (foundML && middleIndex != -1) {
			result.at(1).push_back(laneMiddles.at(middleIndex));
			calculateSolveMatrix(laneMiddles.at(middleIndex), mA, mB, numberOfMiddlePoints);
			middleLaneStartPoint = laneMiddles.at(middleIndex);
			this->middleDistances.at(i-1) = distancesMiddle.at(middleIndex);
			this->middleLineIndices.at(i) = numberOfMiddlePoints;
			numberOfMiddlePoints++;
		}
		if (foundRL && rightIndex != -1 && distancesRight.at(rightIndex) < 100) {
			result.at(2).push_back(laneMiddles.at(rightIndex));
			calculateSolveMatrix(laneMiddles.at(rightIndex), rA, rB, numberOfRightPoints);
			rightLaneStartPoint = laneMiddles.at(rightIndex);
			this->rightDistances.at(i-1) = distancesRight.at(rightIndex);
			this->rightLineIndices.at(i) = numberOfRightPoints;
			numberOfRightPoints++;
		}
	}
}

void PointLaneDetector::removeFalse(std::array<double, numberOfLines>& arr) {
	double summe = std::accumulate(arr.begin(), arr.end(), 0.0);
	double mittelwert = summe / numberOfLines;

	std::array<double, numberOfLines> result;
	std::transform(arr.begin(), arr.end(), result.begin(), [](double elem)->double {
		return elem * elem;
		});
	

	double stdDev = sqrt(std::accumulate(result.begin(), result.end(), 0.0) / numberOfLines - mittelwert * mittelwert);
	std::transform(arr.begin(), arr.end(), arr.begin(), [stdDev](double elem)->double {
		if (elem > stdDev || elem < -stdDev) {
			return 0;
		}
		else {
			return elem;
		}
		});
}

bool PointLaneDetector::solveClothoide() {
	/*doMean(leftDistances);
	doMean(middleDistances);
	doMean(rightDistances);
	std::transform(leftDistances.begin(), leftDistances.end(), leftDistances.begin(), [this](double elem) -> double {
		return (acos(20 / elem));
		});
	std::adjacent_difference(leftDistances.begin(), leftDistances.end(), leftDistances.begin());
	leftDistances.at(0) = 0;

	leftDistances.at(numberOfLines - 2) = 0;
	leftDistances.at(numberOfLines - 1) = 0;
	//removeFalse(this->leftDistances);

	std::array<double, numberOfLines>::iterator posL = std::find_if(leftDistances.begin(), leftDistances.end(), [](double val) ->bool {
		return abs(val) >= 0.05;
		});
	
	int leftIndex = this->leftLineIndices.at(posL - leftDistances.begin());
	int leftTempI = posL - leftDistances.begin();
	while (leftIndex == 0) {
		leftTempI++;
		leftIndex =  this->leftLineIndices.at(leftTempI);
		
	}

	std::adjacent_difference(rightDistances.begin(), rightDistances.end(), rightDistances.begin());
	rightDistances.at(0) = 0;
	std::array<double, numberOfLines>::iterator posR = std::find_if(rightDistances.begin(), rightDistances.end(), [](double val) ->bool {
		return abs(val) >= 0.05;
		});
	int rightIndex = this->rightLineIndices.at(posR - rightDistances.begin());
	int rightTempI = posR - rightDistances.begin();
	while (rightIndex == 0) {
		rightTempI++;
		rightIndex = this->leftLineIndices.at(rightTempI);
		
	}

	int middleTempI = ((posL - leftDistances.begin()) + (posR - rightDistances.begin())) / 2;
	int middleIndex = this->middleLineIndices.at(middleTempI);
	while (middleIndex == 0) {
		middleTempI++;
		middleIndex = this->middleLineIndices.at(middleTempI);
		
	}*/

	int leftIndex = 0;
	int leftTempI = 0;
	int rightIndex = 0;
	int rightTempI = 0;
	int middleTempI = 0;
	int middleIndex = 0;

	intersectionPosL = leftTempI * stepSize;
	intersectionPosM = middleTempI * stepSize;
	intersectionPosR = rightTempI * stepSize;

	Range rowRange = Range(0, numberOfLeftPoints - leftIndex - 1);
	Range colRange = Range(0, this->grade);
	Range zeroOneRange = Range(0, 1);
	bool solveResultL1 = false;
	if (this->foundLL && leftIndex > 2) {
		solveResultL1 = cv::solve(lA(rowRange, colRange), lB(rowRange, zeroOneRange), this->leftLane1, DECOMP_QR);
	}
	bool solveResultM1 = false;
	if (this->foundML && middleIndex > 2) {
		rowRange = Range(0, middleIndex);
		colRange = Range(0, mA.cols);
		solveResultM1 = cv::solve(mA(rowRange, colRange), mB(rowRange, zeroOneRange), this->middleLane1, DECOMP_QR);
	}

	bool solveResultR1 = false;
	if (this->foundRL && rightIndex > 2) {
		rowRange = Range(0, numberOfRightPoints - rightIndex - 1);
		colRange = Range(0, rA.cols);
		solveResultR1 = cv::solve(rA(rowRange, colRange), rB(rowRange, zeroOneRange), this->rightLane1, DECOMP_QR);
	}



	rowRange = Range(leftIndex, numberOfLeftPoints);
	bool solveResultL2 = false;
	if (this->foundLL && (numberOfLeftPoints - leftIndex) > 2) {
		solveResultL2 = cv::solve(lA(rowRange, colRange), lB(rowRange, zeroOneRange), this->leftLane2, DECOMP_QR);
	}
	bool solveResultM2 = false;
	if (this->foundML && (numberOfMiddlePoints - middleIndex) > 2) {
		rowRange = Range(middleIndex, numberOfMiddlePoints);
		colRange = Range(0, mA.cols);
		solveResultM2 = cv::solve(mA(rowRange, colRange), mB(rowRange, zeroOneRange), this->middleLane2, DECOMP_QR);
	}

	bool solveResultR2 = false;
	if (this->foundRL && (numberOfRightPoints - rightIndex) > 2) {
		rowRange = Range(rightIndex, numberOfRightPoints);
		colRange = Range(0, rA.cols);
		solveResultR2 = cv::solve(rA(rowRange, colRange), rB(rowRange, zeroOneRange), this->rightLane2, DECOMP_QR);
	}
	return solveResultL1 && solveResultM1 && solveResultR1 && solveResultL2 && solveResultM2 && solveResultR2;
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
	A.at<double>(i, 0) = point.y * point.y;
	A.at<double>(i, 1) = point.y;
	A.at<double>(i, 2) = 1;
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

