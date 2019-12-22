#include "PointLaneDetector.h"

#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/highgui.hpp>

#include <opencv2/calib3d.hpp>

#include <iostream>

using namespace cv;
using namespace cv::cuda;

PointLaneDetector::PointLaneDetector() {
	this->leftLane = cv::Mat::zeros(this->grade, 1, CV_64F);
	this->middleLane = cv::Mat::zeros(this->grade, 1, CV_64F);
	this->rightLane = cv::Mat::zeros(this->grade, 1, CV_64F);
}

GpuMat edgeDetection(GpuMat image) {
	cuda::GpuMat greyScale;
	cuda::cvtColor(image, greyScale, COLOR_BGR2GRAY);
	Ptr<cuda::CannyEdgeDetector> canny = cuda::createCannyEdgeDetector(700, 200, 3);
	cuda::GpuMat result;
	canny->detect(greyScale, result);
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


void doCalculations(cv::Mat frame, int startLine) {

}


//Detectes the driving lanes for one frame
void PointLaneDetector::calculateFrame(cv::Mat frame) {
	//Upload frame to GPU RAM
	GpuMat upload(frame);
	//Do Canny edge detection
	GpuMat edgeImageGPU = edgeDetection(upload);
	//Download image to RAM
	Mat edgeImage(edgeImageGPU);

	//Mat* splitImage = halfImage(edgeImage);

	Mat lowerHalf = edgeImage;

	internalCalc(lowerHalf, 0);


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
}
VisionResult PointLaneDetector::getResult() {
	return VisionResult();
}

bool PointLaneDetector::internalCalc(cv::Mat frame, int startLine)
{
	const int edgeOffset = 1;
	const int numberOfLines = 60;
	const int stepSize = (frame.rows - edgeOffset) / (numberOfLines - 1);


	cv::Mat lA;				//A
	cv::Mat lB;					//B

	cv::Mat mA;				//A
	cv::Mat mB;				//B

	cv::Mat rA;				//A
	cv::Mat rB;					//B

	int lineY = frame.rows - 2 - stepSize * startLine;											//1: Offset wegen Canny (letzte Zeile schwarz)
	std::vector<std::vector<cv::Point>> detectedPoints;

	//Do the detection for the first line (modifies iterator)
	Mat row = frame.row(lineY);
	Mat linePoints;
	cv::findNonZero(row, linePoints);
	std::vector<cv::Point> laneMiddles = laneMiddlePoints(linePoints, lineY);
	std::cout << laneMiddles;
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

			int llindex = -1;
			double llinitialDistance = 99999999;
			int mlindex = -1;
			double mlinitialDistance = 99999999;
			int rlindex = -1;
			double rlinitialDistance = 99999999;
			for (int distanceIterator = 0; distanceIterator < laneMiddles.size(); distanceIterator++) {
				double lldist = cv::norm(laneMiddles.at(distanceIterator) - leftLaneStartPoint);
				double mldist = cv::norm(laneMiddles.at(distanceIterator) - middleLaneStartPoint);
				double rldist = cv::norm(laneMiddles.at(distanceIterator) - rightLaneStartPoint);
				if (foundLL && lldist < llinitialDistance) {
					if (distanceIterator == mlindex) {
						if (lldist < mlinitialDistance) {
							mlinitialDistance = 999999999;
							mlindex = -1;
							llinitialDistance = lldist;
							llindex = distanceIterator;
						}
					}
					else if (distanceIterator == rlindex) {
						if (lldist < rlinitialDistance) {
							rlinitialDistance = 999999999;
							rlindex = -1;
							llinitialDistance = lldist;
							llindex = distanceIterator;
						}
					}
					else {
						llinitialDistance = lldist;
						llindex = distanceIterator;
					}

				}
				if (foundML && mldist < mlinitialDistance) {
					if (distanceIterator == llindex) {
						if (mldist < llinitialDistance) {
							llinitialDistance = 999999999;
							llindex = -1;
							mlinitialDistance = mldist;
							mlindex = distanceIterator;
						}
					}
					else if (distanceIterator == rlindex) {
						if (mldist < rlinitialDistance) {
							rlinitialDistance = 999999999;
							rlindex = -1;
							mlinitialDistance = mldist;
							mlindex = distanceIterator;
						}
					}
					else {
						mlinitialDistance = mldist;
						mlindex = distanceIterator;
					}
				}
				if (foundML && mldist < mlinitialDistance) {
					if (distanceIterator == llindex) {
						if (rldist < llinitialDistance) {
							llinitialDistance = 999999999;
							llindex = -1;
							rlinitialDistance = rldist;
							rlindex = distanceIterator;
						}
					}
					else if (distanceIterator == mlindex) {
						if (rldist < mlinitialDistance) {
							mlinitialDistance = 999999999;
							mlindex = -1;
							rlinitialDistance = rldist;
							rlindex = distanceIterator;
						}
					}
					else {
						rlinitialDistance = rldist;
						rlindex = distanceIterator;
					}
				}
			}

			if (foundLL && llindex != -1) {
				result.at(0).push_back(laneMiddles.at(llindex));
				calculateSolveMatrix(laneMiddles.at(llindex), lA, lB);
			}
			if (foundML && mlindex != -1) {
				result.at(1).push_back(laneMiddles.at(mlindex));
				calculateSolveMatrix(laneMiddles.at(mlindex), mA, mB);
			}
			if (foundRL && rlindex != -1) {
				result.at(2).push_back(laneMiddles.at(rlindex));
				calculateSolveMatrix(laneMiddles.at(rlindex), rA, rB);
			}
		}
		lineY -= stepSize;
	}

	std::cout << lA << std::endl;

	std::cout << lB << std::endl;
	std::cout << mA << std::endl;
	std::cout << mB << std::endl;


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