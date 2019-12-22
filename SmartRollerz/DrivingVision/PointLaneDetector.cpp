#include "PointLaneDetector.h"

#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/highgui.hpp>

#include <opencv2/calib3d.hpp>

#include <iostream>
#include <chrono>

using namespace cv;
using namespace cv::cuda;

PointLaneDetector::PointLaneDetector() {
	this->leftLane = cv::Mat::zeros(this->grade, 1, CV_64F);
	this->middleLane = cv::Mat::zeros(this->grade, 1, CV_64F);
	this->rightLane = cv::Mat::zeros(this->grade, 1, CV_64F);
}

GpuMat edgeDetection(GpuMat image) {
	//cuda::GpuMat greyScale;
	//cuda::cvtColor(image, greyScale, COLOR_BGR2GRAY);
	Ptr<cuda::CannyEdgeDetector> canny = cuda::createCannyEdgeDetector(700, 200, 3);
	cuda::GpuMat result;
	canny->detect(image, result);
	return result;
}

Mat* halfImage(Mat image) {
	Mat* result = new Mat[2];
	Rect upperHalfSize = Rect(0, 0, image.cols, image.rows / 2);
	result[0] = image(upperHalfSize);

	Rect lowerHalfSize = Rect(0, image.rows / 2, image.cols, image.rows / 2);
	result[1] = image(lowerHalfSize);
	return result;
}


#define LANE_THRES_MIN 5
#define LANE_THRES_MAX 60
#define LL_MIN_X	670
#define LL_MAX_X	690
#define ML_MIN_X	780
#define ML_MAX_X	800
#define RL_MIN_X	880
#define RL_MAX_X	900

std::vector<cv::Point> PointLaneDetector::laneMiddlePoints(Mat linePoints, int yPos) {
	std::vector<cv::Point> laneMiddles;
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
	return laneMiddles;
}

double calcX(cv::Mat func, float y) {
	double res = 0;
	for (int i = 0; i < func.rows; i++) {
		double num = func.at<double>(i, 0);
		res = res + num * pow(y, func.rows - 1 - i);
	}
	return res;
}

void calculateSolveMatrix(Point point, cv::Mat& A, cv::Mat& B) {
	double xValue = point.x;
	double yValue = point.y;
	//TODO statt 3 grade
	cv::Mat aRow = cv::Mat::zeros(1, 3, CV_64F);
	aRow.at<double>(0, 0) = yValue * yValue;
	aRow.at<double>(0, 1) = yValue;
	aRow.at<double>(0, 2) = 1;
	A.push_back(aRow);
	cv::Mat bRow = cv::Mat::zeros(1, 1, CV_64F);
	bRow.at<double>(0, 0) = point.x;
	B.push_back(bRow);
}

void drawResult(cv::Mat im, cv::Mat x, cv::Scalar color) {
	for (int row = 0; row < im.rows; row++) {
		cv::Mat column = im.row(row);
		int type = column.type();

		float val = calcX(x, row);
		if (val <= im.cols - 1 && val >= 0) {
			//std::cout << row << "::" << val << std::endl;
			circle(im, (cv::Point((int)val, row)), 1, color);
		}
	}
}


//Detectes the driving lanes for one frame
void PointLaneDetector::calculateFrame(cv::Mat frame) {
	system("cls");
	auto start = std::chrono::high_resolution_clock::now();
	//Upload frame to GPU RAM
	GpuMat upload(frame);
	//Do Canny edge detection
	GpuMat edgeImageGPU = edgeDetection(upload);
	//Download image to RAM
	Mat edgeImage(edgeImageGPU);
	auto cannyEnd = std::chrono::high_resolution_clock::now();
	//Mat* splitImage = halfImage(edgeImage);

	Mat lowerHalf = edgeImage;
	internalCalc(lowerHalf, 0);
	auto algorithmEnd = std::chrono::high_resolution_clock::now();

	cv::cvtColor(lowerHalf, lowerHalf, COLOR_GRAY2BGR);
	drawResult(lowerHalf, this->leftLane, Scalar(255, 0, 0));
	drawResult(lowerHalf, this->middleLane, Scalar(0, 255, 0));
	drawResult(lowerHalf, this->rightLane, Scalar(0, 0, 255));


	for (int x = 0; x < this->result.size(); x++) {
		for (int y = 0; y < this->result.at(x).size(); y++) {
			circle(lowerHalf, this->result.at(x).at(y), 5, Scalar(x, 255, 255));
		}
	}

	imshow("TEST", lowerHalf);
	auto totalEnd = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(algorithmEnd - start).count();
	std::cout << "Laufzeit gesamt: " << duration << " ms" << std::endl;

	duration = std::chrono::duration_cast<std::chrono::microseconds>(cannyEnd - start).count();
	std::cout << "Laufzeit GPU (Canny): " << duration << " ms" << std::endl;

	duration = std::chrono::duration_cast<std::chrono::microseconds>(algorithmEnd - cannyEnd).count();
	std::cout << "Laufzeit Algorithmus (CPU): " << duration << " ms" << std::endl;

	//duration = std::chrono::duration_cast<std::chrono::microseconds>(totalEnd - algorithmEnd).count();
	//std::cout << "Laufzeit Darstellung: " << duration << " ms" << std::endl;




}
VisionResult PointLaneDetector::getResult() {
	return VisionResult();
}

void calculateDistance(cv::Point a, cv::Point reference) {

}

bool PointLaneDetector::internalCalc(cv::Mat frame, int startLine)
{
	const int edgeOffset = 1;
	const int numberOfLines = 60;
	const int stepSize = (frame.rows - edgeOffset) / (numberOfLines - 1);


	cv::Mat lA;				
	cv::Mat lB;					

	cv::Mat mA;				
	cv::Mat mB;				

	cv::Mat rA;				
	cv::Mat rB;					

	int lineY = frame.rows - 2 - stepSize * startLine;											//1: Offset wegen Canny (letzte Zeile schwarz)
	std::vector<std::vector<cv::Point>> detectedPoints;

	//Do the detection for the first line (modifies iterator)
	Mat row = frame.row(lineY);
	Mat linePoints;
	cv::findNonZero(row, linePoints);
	std::vector<cv::Point> laneMiddles = laneMiddlePoints(linePoints, lineY);
	detectedPoints.push_back(laneMiddles);
	lineY -= stepSize;

	std::vector<cv::Point> firstLine = detectedPoints.at(0);
	int numberOfDetectionsFL = firstLine.size();

	cv::Point leftLaneStartPoint, middleLaneStartPoint, rightLaneStartPoint;
	bool foundLL = false;
	bool foundML = false;
	bool foundRL = false;
	if (numberOfDetectionsFL < 2) {
		//Again with next line

	}
	else {
		for (int pointI = 0; pointI < firstLine.size(); pointI++) {
			cv::Point analysisPoint = firstLine.at(pointI);

			if (analysisPoint.x > LL_MIN_X&& analysisPoint.x < LL_MAX_X) {
				foundLL = true;
				leftLaneStartPoint = analysisPoint;
				result.at(0).push_back(analysisPoint);
				calculateSolveMatrix(analysisPoint, lA, lB);
			}
			else if (analysisPoint.x > ML_MIN_X&& analysisPoint.x < ML_MAX_X) {
				foundML = true;
				middleLaneStartPoint = analysisPoint;
				result.at(1).push_back(analysisPoint);
				calculateSolveMatrix(analysisPoint, mA, mB);
			}
			else if (analysisPoint.x > RL_MIN_X&& analysisPoint.x < RL_MAX_X) {
				foundRL = true;
				rightLaneStartPoint = analysisPoint;
				result.at(2).push_back(analysisPoint);
				calculateSolveMatrix(analysisPoint, rA, rB);
			}
		}
	}

	//If not all lines are found -> do it again!

	for (int i = 1; i < numberOfLines; i++) {
		Mat row = frame.row(lineY);
		Mat linePoints;
		cv::findNonZero(row, linePoints);
		std::vector<cv::Point> laneMiddles = laneMiddlePoints(linePoints, lineY);
		if (!laneMiddles.empty()) {
			detectedPoints.push_back(laneMiddles);
			std::vector<double> distancesLeft;
			distancesLeft.reserve(laneMiddles.size());

			std::vector<double> distancesMiddle;
			distancesMiddle.reserve(laneMiddles.size());

			std::vector<double> distancesRight;
			distancesRight.reserve(laneMiddles.size());

			std::for_each(laneMiddles.begin(), laneMiddles.end(),
				[leftLaneStartPoint, middleLaneStartPoint, rightLaneStartPoint, &distancesLeft, &distancesMiddle, &distancesRight](cv::Point pt) -> void {
					distancesLeft.push_back(cv::norm(pt - leftLaneStartPoint));
					distancesMiddle.push_back(cv::norm(pt - middleLaneStartPoint));
					distancesRight.push_back(cv::norm(pt - rightLaneStartPoint));
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


			if (foundLL && leftIndex != -1) {
				result.at(0).push_back(laneMiddles.at(leftIndex));
				calculateSolveMatrix(laneMiddles.at(leftIndex), lA, lB);
			}
			if (foundML && middleIndex != -1) {
				result.at(1).push_back(laneMiddles.at(middleIndex));
				calculateSolveMatrix(laneMiddles.at(middleIndex), mA, mB);
			}
			if (foundRL && rightIndex != -1) {
				result.at(2).push_back(laneMiddles.at(rightIndex));
				calculateSolveMatrix(laneMiddles.at(rightIndex), rA, rB);
			}
		}
		lineY -= stepSize;
	}

	bool solveResultL = cv::solve(lA, lB, this->leftLane, DECOMP_QR);
	bool solveResultM = cv::solve(mA, mB, this->middleLane, DECOMP_QR);
	bool solveResultR = cv::solve(rA, rB, this->rightLane, DECOMP_QR);
	return solveResultL && solveResultM && solveResultR;
}

/*for (int i = 0; i < laneMiddles.size(); i++) {
			Point pt;
			pt.x = laneMiddles[i].x;
			pt.y = lineY;
			circle(lowerHalf, pt, 5, Scalar(255, 255, 255));
		}

		/*for (int i = 0; i < linePoints.total(); i++) {
			//std::cout << "Zero#" << i << ": " << linePoints.at<cv::Point>(i).x << ", " << linePoints.at<cv::Point>(i).y << std::endl;
			Point pt = linePoints.at<cv::Point>(i);
			pt.y = lineY;
			//circle(lowerHalf, pt, 5, Scalar(255, 255, 255));
		}
		line(lowerHalf, Point(0, lineY), Point(lowerHalf.cols, lineY), Scalar(255, 255, 255));
		*/