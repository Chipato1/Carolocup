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

/*
Point3f convertToRealWorldPoint() {
	/*std::vector<cv::Point2f> imagePoints;
	std::vector<cv::Point3f> objectPoints;
	//img points are green dots in the picture
	imagePoints.push_back(cv::Point2f(271., 109.));
	imagePoints.push_back(cv::Point2f(65., 208.));
	imagePoints.push_back(cv::Point2f(334., 459.));
	imagePoints.push_back(cv::Point2f(600., 225.));

	//object points are measured in millimeters because calibration is done in mm also
	objectPoints.push_back(cv::Point3f(0., 0., 0.));
	objectPoints.push_back(cv::Point3f(-511., 2181., 0.));
	objectPoints.push_back(cv::Point3f(-3574., 2354., 0.));
	objectPoints.push_back(cv::Point3f(-3400., 0., 0.));

	cv::Mat rvec(1, 3, cv::DataType<double>::type);
	cv::Mat tvec(1, 3, cv::DataType<double>::type);
	cv::Mat rotationMatrix(3, 3, cv::DataType<double>::type);

	cv::solvePnP(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec);
	cv::Rodrigues(rvec, rotationMatrix);

	cv::Mat uvPoint = (cv::Mat_<double>(3, 1) << 363, 222, 1); // u = 363, v = 222, got this point using mouse callback

	cv::Mat leftSideMat = rotationMatrix.inv() * cameraMatrix.inv() * uvPoint;
	cv::Mat rightSideMat = rotationMatrix.inv() * tvec;

	double s = (285 + rightSideMat.at<double>(2, 0)) / leftSideMat.at<double>(2, 0));
	//285 represents the height Zconst

	std::cout << "P = " << rotationMatrix.inv() * (s * cameraMatrix.inv() * uvPoint - tvec) << std::endl;
}*/

#define LANE_THRES_MIN 15
#define LANE_THRES_MAX 40

std::vector<cv::Point> laneMiddlePoints(Mat linePoints, int yPos) {
	std::vector<cv::Point> laneMiddles;
	for (int i = 1; i < linePoints.total(); i++) {
		Point pt1 = linePoints.at<cv::Point>(i-1);
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

float calcY(cv::Mat func, float x) {
	return func.at<double>(0,0) * x * x + func.at<double>(1, 0) * x + func.at<double>(2, 0);
}

void calculateSolveMatrix(Point point, cv::Mat A, cv::Mat B, int i) {
		double xValue = point.x;
		double yValue = point.y;
		A.at<double>(i, 0) = xValue * xValue;
		A.at<double>(i, 1) = xValue;
		A.at<double>(i, 2) = 1;
		
		B.at<double>(i, 0) = point.y;
}




void PointLaneDetector::calculateFrame(cv::Mat frame) {
	Mat A = Mat::zeros(3, 3, CV_64F);	//Zeile, Spalte

	//Zeile 1
	A.at<double>(0, 0) = 1;
	A.at<double>(0, 1) = -1;
	A.at<double>(0, 2) = 1;

	//Zeile 2
	A.at<double>(1, 0) = 0;
	A.at<double>(1, 1) = 0;
	A.at<double>(1, 2) = 1;

	//Zeile 3
	A.at<double>(2, 0) = 1;
	A.at<double>(2, 1) = 1;
	A.at<double>(2, 2) = 1;

	Mat B = Mat::zeros(3, 1, CV_64F);
	B.at<double>(0, 0) = 1;
	B.at<double>(1, 0) = 0;
	B.at<double>(2, 0) = 1;

	Mat x = Mat::zeros(3, 1, CV_64F);
	x.at<double>(0, 0) = 0;
	x.at<double>(1, 0) = 0;
	x.at<double>(2, 0) = 0;

	std::cout << x << std::endl;


	int flags = DECOMP_QR;
	cv::solve(A, B, x, flags);
	std::cout << x << std::endl;

	GpuMat upload(frame);
	GpuMat edgeImageGPU = edgeDetection(upload);
	Mat edgeImage(edgeImageGPU);

	Mat* splitImage = halfImage(edgeImage);

	Mat lowerHalf = edgeImage;
	
	
	const int edgeOffset = 20;
	const int numberOfLines = 30;
	const int stepSize = (lowerHalf.rows - 2* edgeOffset)/numberOfLines;

	A = cv::Mat::zeros(numberOfLines, 3, CV_64F);				//A
	x = cv::Mat::zeros(3, 1, CV_64F);								//X
	B = cv::Mat::zeros(numberOfLines, 1, CV_64F);				//B

	int lineY = edgeOffset;
	for (int i = 0; i < numberOfLines; i++) {
		Mat row = lowerHalf.row(lineY);
		Mat linePoints;
		cv::findNonZero(row, linePoints);
		std::vector<cv::Point> laneMiddles = laneMiddlePoints(linePoints, lineY);
		
		calculateSolveMatrix(laneMiddles.at(0),A, B, i);
		

		for (int i = 0; i < laneMiddles.size(); i++) {
			Point pt;
			pt.x = laneMiddles[i].x;
			pt.y = lineY;
			circle(lowerHalf, pt, 5, Scalar(255, 255, 255));
		}

		for (int i = 0; i < linePoints.total(); i++) {
			//std::cout << "Zero#" << i << ": " << linePoints.at<cv::Point>(i).x << ", " << linePoints.at<cv::Point>(i).y << std::endl;
			Point pt = linePoints.at<cv::Point>(i);
			pt.y = lineY;
			//circle(lowerHalf, pt, 5, Scalar(255, 255, 255));
		}
		line(lowerHalf, Point(0, lineY), Point(lowerHalf.cols, lineY), Scalar(255, 255, 255));
		lineY += stepSize;
	}
	std::cout << "A:";
	std::cout << A << std::endl;
	std::cout << "B:";
	std::cout << B << std::endl;
	std::cout << "x:";
	std::cout << x << std::endl;
	bool solveResult = cv::solve(A, B, x, flags);
	if (solveResult == true) {
		std::cout << "Result: " << x << std::endl;
	}
	else {
		std::cout << "Failed" << std::endl;
	}
	imshow("TEST", lowerHalf);
}
VisionResult PointLaneDetector::getResult() {
	return VisionResult();
}