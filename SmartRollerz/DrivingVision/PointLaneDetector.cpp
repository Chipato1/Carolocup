#include "PointLaneDetector.h"

#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/cudawarping.hpp>

#include <opencv2/calib3d.hpp>

#include <iostream>
#include <chrono>
#define _USE_MATH_DEFINES
#include <math.h>

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


	int alpha_ = 30, beta_ = 90, gamma_ = 90;
	int f_ = 500, dist_ = 0, skew_ = 0;             //skew ist SchrŠglageparameter (dreht das Bild nach Rechts oder Links) ->VollstŠndigkeit

    //TODO: dist_ aendern
    dist_ = 82;
    
	double focalLength, dist, alpha, beta, gamma, skew;

	alpha = ((double)alpha_ - 90) * M_PI / 180;
	beta = ((double)beta_ - 90) * M_PI / 180;
	gamma = ((double)gamma_ - 90) * M_PI / 180;
	focalLength = (double)f_;
    
    //TODO: dist ist eigentlich: dist = (KamHšhe/sin((180-KameraWinkel)))
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
		focalLength, skew, w / 2, 0,
		0, focalLength, h / 2, 0,
		0, 0, 1, 0
		);


	transformationMat = K * (T * (R * A1));
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
#define LL_MAX_X	730
#define ML_MIN_X	780
#define ML_MAX_X	820
#define RL_MIN_X	900
#define RL_MAX_X	930

/*#define LANE_THRES_MIN 5
#define LANE_THRES_MAX 60
#define LL_MIN_X	400
#define LL_MAX_X	550
#define ML_MIN_X	670
#define ML_MAX_X	800
#define RL_MIN_X	1000
#define RL_MAX_X	1200*/

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
	GpuMat ddown;
	cv::cuda::warpPerspective(upload, ddown,this->transformationMat, frame.size(), INTER_CUBIC | WARP_INVERSE_MAP);
	//cv::Mat down(ddown);
	//imshow("TESTer", down);
	canny->detect(ddown, upload);
	auto downloadZeit = std::chrono::high_resolution_clock::now();
	std::cout << transformationMat << std::endl;
	


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
				circle(lowerHalf, this->result.at(x).at(y), 5, Scalar(x*128, 255, 255));
			}
	}
	cv::resize(lowerHalf, lowerHalf, Size(1000, 750));
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


static cv::Mat InversePerspectiveMapping(cv::Mat input, int w, int h, int n) {// w : width and h : height

	Point2f inputPts[4] = { Point2f(0,0),Point2f(1600,0), Point2f(0,1200), Point2f(1600,1200) };
	Point2f outputPts[4] = { Point2f(0,0),Point2f(0,0), Point2f(0,0), Point2f(0,0) };

	cv::Mat output, M;  //create the output matrice

	 M = cv::getPerspectiveTransform(inputPts, outputPts);


	cv::cuda::GpuMat gpuOutput;
	cv::cuda::GpuMat gpuInput = cv::cuda::GpuMat(input);

	cv::cuda::warpPerspective(gpuInput, gpuOutput, M, cv::Size(w, h), INTER_LINEAR, BORDER_CONSTANT, 0, Stream::Null());

	gpuOutput.download(output);
	gpuOutput.release();
	gpuInput.release();

	
	imshow("left_IPM", output);
	return output;
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

	Mat linePoints;
	std::vector<cv::Point> laneMiddles;
	laneMiddles.reserve(25);

	cv::Point leftLaneStartPoint, middleLaneStartPoint, rightLaneStartPoint;
	bool foundLL = false;
	bool foundML = false;
	bool foundRL = false;
	bool hasMiddleLane = false;

	int numberOfLeftPoints = 0;
	int numberOfMiddlePoints = 0;
	int numberOfRightPoints = 0;

	//If not all lines are found -> do it again!

	auto minima = std::chrono::high_resolution_clock::now();
	auto ergebnis = std::chrono::high_resolution_clock::now();
	auto distanzen = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < numberOfLines; i++) {
		auto startBerechnung = std::chrono::high_resolution_clock::now();
		cv::findNonZero(frame.row(lineY), linePoints);
		auto nonZero = std::chrono::high_resolution_clock::now();
		laneMiddlePoints(laneMiddles, linePoints, lineY);
		auto mittelpunkte = std::chrono::high_resolution_clock::now();
		auto distStart = std::chrono::high_resolution_clock::now();
		if (!laneMiddles.empty()) {
			detectedPoints.push_back(laneMiddles);
			//Wenn eine der Linien noch nicht erkannt wurde...
			if (!foundLL || !foundML || !foundRL) {
				for (int pointI = 0; pointI < laneMiddles.size(); pointI++) {
					cv::Point analysisPoint = laneMiddles.at(pointI);

					if (analysisPoint.x > LL_MIN_X&& analysisPoint.x < LL_MAX_X) {
						if (!foundLL) {
							foundLL = true;
							leftLaneStartPoint = analysisPoint;
							result.at(0).push_back(analysisPoint);
							calculateSolveMatrix(analysisPoint, lA, lB, numberOfLeftPoints);
							laneMiddles.erase(laneMiddles.begin() + pointI);
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
							numberOfRightPoints++;
						}
					}
				}
			}
			if (foundLL || foundML || foundRL) {
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
						foundML = false;
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
					calculateSolveMatrix(laneMiddles.at(leftIndex), lA, lB, numberOfLeftPoints);
					leftLaneStartPoint = laneMiddles.at(leftIndex);
					numberOfLeftPoints++;
				}
				if (foundML && middleIndex != -1) {
					result.at(1).push_back(laneMiddles.at(middleIndex));
					calculateSolveMatrix(laneMiddles.at(middleIndex), mA, mB, numberOfMiddlePoints);
					middleLaneStartPoint = laneMiddles.at(middleIndex);
					numberOfMiddlePoints++;
				}
				if (foundRL && rightIndex != -1) {
					result.at(2).push_back(laneMiddles.at(rightIndex));
					calculateSolveMatrix(laneMiddles.at(rightIndex), rA, rB, numberOfRightPoints);
					rightLaneStartPoint = laneMiddles.at(rightIndex);
					numberOfRightPoints++;
				}
				ergebnis = std::chrono::high_resolution_clock::now();

			}
			
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
	bool solveResultL = false; 
	if (foundLL) {
		solveResultL = cv::solve(lA(r1, r2), lB(r1, r3), this->leftLane, DECOMP_QR);
	}
	bool solveResultM = false;
	if (foundML) {
		r1 = Range(0, numberOfMiddlePoints);
		r2 = Range(0, mA.cols);
		solveResultM = cv::solve(mA(r1, r2), mB(r1, r3), this->middleLane, DECOMP_QR);
	}
	std::cout << lA << std::endl;
	std::cout << lB << std::endl;
	bool solveResultR = false;
	if (foundRL) {
		r1 = Range(0, numberOfRightPoints);
		r2 = Range(0, rA.cols);
		solveResultR = cv::solve(rA(r1, r2), rB(r1, r3), this->rightLane, DECOMP_QR);
	}
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
