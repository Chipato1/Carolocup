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

	lA = cv::Mat::zeros(numberOfLines, grade, CV_64F);
	lB = cv::Mat::zeros(numberOfLines, 1, CV_64F);

	mA = cv::Mat::zeros(numberOfLines, grade, CV_64F);
	mB = cv::Mat::zeros(numberOfLines, 1, CV_64F);

	rA = cv::Mat::zeros(numberOfLines, grade, CV_64F);
	rB = cv::Mat::zeros(numberOfLines, 1, CV_64F);

	canny = cuda::createCannyEdgeDetector(700, 200, 3);
}

GpuMat PointLaneDetector::edgeDetection(GpuMat& image) {
	//cuda::GpuMat greyScale;
	//cuda::cvtColor(image, greyScale, COLOR_BGR2GRAY);
	
	
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
	laneMiddles.reserve(linePoints.total());
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

void calculateSolveMatrix(Point point, cv::Mat& A, cv::Mat& B, int i) {
	double xValue = point.x;
	double yValue = point.y;
	A.at<double>(i, 0) = yValue * yValue;
	A.at<double>(i, 1) = yValue;
	A.at<double>(i, 2) = 1;

	B.at<double>(i, 0) = point.x;
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
auto allokierung = std::chrono::high_resolution_clock::now();
auto ersteBerechnung = std::chrono::high_resolution_clock::now();
auto loop = std::chrono::high_resolution_clock::now();
auto solveZeit = std::chrono::high_resolution_clock::now();

//Detectes the driving lanes for one frame
void PointLaneDetector::calculateFrame(cv::Mat frame) {
	system("cls");
	auto start = std::chrono::high_resolution_clock::now();
	//Upload frame to GPU RAM
	GpuMat upload(frame);
	auto uploadZeit = std::chrono::high_resolution_clock::now();
	//Do Canny edge detection
	//GpuMat edgeImageGPU = edgeDetection(upload);
	canny->detect(upload, upload);
	auto downloadZeit = std::chrono::high_resolution_clock::now();
	//Download image to RAM
	Mat edgeImage(upload);
	auto cannyEnd = std::chrono::high_resolution_clock::now();
	//Mat* splitImage = halfImage(edgeImage);

	Mat lowerHalf = edgeImage;

	auto algorithmStart = std::chrono::high_resolution_clock::now();
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
	std::cout << "----------------------------------" << std::endl;
	std::cout << "Laufzeit gesamt: \t\t\t" << duration << " us" << std::endl;
	std::cout << "----------------------------------" << std::endl;
	duration = std::chrono::duration_cast<std::chrono::microseconds>(cannyEnd - start).count();
	std::cout << "Laufzeit GPU (Gesamt): \t\t\t" << duration << " us" << std::endl;

	duration = std::chrono::duration_cast<std::chrono::microseconds>(uploadZeit - start).count();
	std::cout << "Zeit für GPU (Upload): \t\t\t" << duration << " us" << std::endl;

	duration = std::chrono::duration_cast<std::chrono::microseconds>(downloadZeit - uploadZeit).count();
	std::cout << "Zeit für GPU (Canny Edge Detector): \t" << duration << " us" << std::endl;


	duration = std::chrono::duration_cast<std::chrono::microseconds>(cannyEnd - downloadZeit).count();
	std::cout << "Zeit für GPU (Download): \t\t" << duration << " us" << std::endl;


	std::cout << "----------------------------------" << std::endl;
	duration = std::chrono::duration_cast<std::chrono::microseconds>(algorithmEnd - cannyEnd).count();
	std::cout << "Laufzeit Algorithmus (Gesamt) (CPU): \t\t" << duration << " us" << std::endl;

	duration = std::chrono::duration_cast<std::chrono::microseconds>(allokierung - algorithmStart).count();
	std::cout << "Laufzeit Algorithmus (Speicher) (CPU): \t\t" << duration << " us" << std::endl;

	duration = std::chrono::duration_cast<std::chrono::microseconds>(ersteBerechnung - allokierung).count();
	std::cout << "Laufzeit Algorithmus (Klassifizierung) (CPU): \t" << duration << " us" << std::endl;

	duration = std::chrono::duration_cast<std::chrono::microseconds>(loop - ersteBerechnung).count();
	std::cout << "Laufzeit Algorithmus (Punktfindung) (CPU): \t" << duration << " us" << std::endl;

	duration = std::chrono::duration_cast<std::chrono::microseconds>(solveZeit - loop).count();
	std::cout << "Laufzeit Algorithmus (Lösung) (CPU): \t\t" << duration << " us" << std::endl;

}

VisionResult PointLaneDetector::getResult() {
	return VisionResult();
}



bool PointLaneDetector::internalCalc(cv::Mat frame, int startLine)
{
	
	const int stepSize = (frame.rows - edgeOffset) / (numberOfLines - 1);

	result.at(0).clear();
	result.at(0).reserve(numberOfLines);
	result.at(1).clear();
	result.at(1).reserve(numberOfLines);
	result.at(2).clear();
	result.at(2).reserve(numberOfLines);



	allokierung = std::chrono::high_resolution_clock::now();

	int lineY = frame.rows - 2 - stepSize * startLine;											//1: Offset wegen Canny (letzte Zeile schwarz)
	std::vector<std::vector<cv::Point>> detectedPoints;
	detectedPoints.reserve(numberOfLines);

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

	int numberOfLeftPoints = 0;
	int numberOfMiddlePoints = 0;
	int numberOfRightPoints = 0;

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
				calculateSolveMatrix(analysisPoint, lA, lB,0);
				numberOfLeftPoints++;
			}
			else if (analysisPoint.x > ML_MIN_X&& analysisPoint.x < ML_MAX_X) {
				foundML = true;
				middleLaneStartPoint = analysisPoint;
				result.at(1).push_back(analysisPoint);
				calculateSolveMatrix(analysisPoint, mA, mB,0);
				numberOfMiddlePoints++;
			}
			else if (analysisPoint.x > RL_MIN_X&& analysisPoint.x < RL_MAX_X) {
				foundRL = true;
				rightLaneStartPoint = analysisPoint;
				result.at(2).push_back(analysisPoint);
				calculateSolveMatrix(analysisPoint, rA, rB,0);
				numberOfRightPoints++;
			}
		}
	}
	ersteBerechnung = std::chrono::high_resolution_clock::now();
	//If not all lines are found -> do it again!

	auto minima = std::chrono::high_resolution_clock::now();
	auto ergebnis = std::chrono::high_resolution_clock::now();
	auto distanzen = std::chrono::high_resolution_clock::now();
	
	for (int i = 1; i < numberOfLines; i++) {
		auto startBerechnung = std::chrono::high_resolution_clock::now();
		Mat row = frame.row(lineY);
		
		Mat linePoints;
		cv::findNonZero(row, linePoints);
		auto nonZero = std::chrono::high_resolution_clock::now();
		std::vector<cv::Point> laneMiddles = laneMiddlePoints(linePoints, lineY);
		auto mittelpunkte = std::chrono::high_resolution_clock::now();
		auto distStart = std::chrono::high_resolution_clock::now();
		if (!laneMiddles.empty()) {
			detectedPoints.push_back(laneMiddles);

			distStart = std::chrono::high_resolution_clock::now();
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
			distanzen = std::chrono::high_resolution_clock::now();
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
			minima = std::chrono::high_resolution_clock::now();
			if (foundLL && leftIndex != -1) {
				result.at(0).push_back(laneMiddles.at(leftIndex));
				calculateSolveMatrix(laneMiddles.at(leftIndex), lA, lB,i);
				numberOfLeftPoints++;
			}
			if (foundML && middleIndex != -1) {
				result.at(1).push_back(laneMiddles.at(middleIndex));
				calculateSolveMatrix(laneMiddles.at(middleIndex), mA, mB,i);
				numberOfMiddlePoints++;
			}
			if (foundRL && rightIndex != -1) {
				result.at(2).push_back(laneMiddles.at(rightIndex));
				calculateSolveMatrix(laneMiddles.at(rightIndex), rA, rB,i);
				numberOfRightPoints++;
			}
			ergebnis = std::chrono::high_resolution_clock::now();
		}

		/*std::cout << "----------------------------------" << std::endl;
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(nonZero - startBerechnung).count();
		std::cout << "NonZero \t\t" << duration << " us" << std::endl;

		duration = std::chrono::duration_cast<std::chrono::microseconds>(mittelpunkte - nonZero).count();
		std::cout << "Mittelpunkte \t\t" << duration << " us" << std::endl;

		duration = std::chrono::duration_cast<std::chrono::microseconds>(distanzen - distStart).count();
		std::cout << "Dist: \t\t" << duration << " us" << std::endl;

		duration = std::chrono::duration_cast<std::chrono::microseconds>(minima - distanzen).count();
		std::cout << "Minima: \t" << duration << " us" << std::endl;

		duration = std::chrono::duration_cast<std::chrono::microseconds>(ergebnis - minima).count();
		std::cout << "Ergebnis: \t" << duration << " us" << std::endl;*/


		lineY -= stepSize;
	}
	loop = std::chrono::high_resolution_clock::now();
	Range r1 = Range(0, numberOfLeftPoints);
	Range r2 = Range(0, lA.cols);
	Range r3 = Range(0, 1);
	bool solveResultL = cv::solve(lA(r1,r2), lB(r1,r3), this->leftLane, DECOMP_QR);
	r1 = Range(0, numberOfMiddlePoints);
	r2 = Range(0, mA.cols);
	bool solveResultM = cv::solve(mA(r1,r2), mB(r1,r3), this->middleLane, DECOMP_QR);
	r1 = Range(0, numberOfRightPoints);
	r2 = Range(0, rA.cols);
	bool solveResultR = cv::solve(rA(r1,r2), rB(r1,r3), this->rightLane, DECOMP_QR);
	solveZeit = std::chrono::high_resolution_clock::now();
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