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
#define LANE_THRES_MAX 60

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

float calcX(cv::Mat func, float y) {
	return func.at<double>(0,0) * y * y + func.at<double>(1, 0) * y + func.at<double>(2, 0);
}

void calculateSolveMatrix(Point point, cv::Mat A, cv::Mat B, int i) {
		double xValue = point.x;
		double yValue = point.y;
		A.at<double>(i, 0) = yValue * yValue;
		A.at<double>(i, 1) = yValue;
		A.at<double>(i, 2) = 1;
		
		B.at<double>(i, 0) = point.x;
}




void PointLaneDetector::calculateFrame(cv::Mat frame) {
	GpuMat upload(frame);
	GpuMat edgeImageGPU = edgeDetection(upload);
	Mat edgeImage(edgeImageGPU);

	//Mat* splitImage = halfImage(edgeImage);

	Mat lowerHalf = edgeImage;
	
	
	const int edgeOffset = 1;
	const int numberOfLines = 30;
	const int stepSize = (lowerHalf.rows - edgeOffset)/numberOfLines;

	cv::Mat A = cv::Mat::zeros(numberOfLines, 3, CV_64F);				//A
	cv::Mat x = cv::Mat::zeros(3, 1, CV_64F);							//X
	cv::Mat B = cv::Mat::zeros(numberOfLines, 1, CV_64F);				//B

	int lineY = lowerHalf.rows - 2;										//1: Offset wegen Canny (letzte Zeile schwarz)
	for (int i = numberOfLines - 1; i > 0; i--) {
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

		/*for (int i = 0; i < linePoints.total(); i++) {
			//std::cout << "Zero#" << i << ": " << linePoints.at<cv::Point>(i).x << ", " << linePoints.at<cv::Point>(i).y << std::endl;
			Point pt = linePoints.at<cv::Point>(i);
			pt.y = lineY;
			//circle(lowerHalf, pt, 5, Scalar(255, 255, 255));
		}*/
		line(lowerHalf, Point(0, lineY), Point(lowerHalf.cols, lineY), Scalar(255, 255, 255));
		lineY -= stepSize;
	}

	bool solveResult = cv::solve(A, B, x, DECOMP_QR);
	if (solveResult == true) {
		//std::cout << "Result: " << x << std::endl;
	}
	else {
		//std::cout << "Failed" << std::endl;
	}

	for (int row = 0; row < lowerHalf.rows; row++) {
		cv::Mat column = lowerHalf.row(row);
		int type = column.type();

		float val = calcX(x, row);
		if (val <= lowerHalf.cols-1 && val >= 0) {
			//std::cout << row << "::" << val << std::endl;
			circle(lowerHalf, (cv::Point((int)val, row)), 1, Scalar(255, 255, 255));
		}
	}

	imshow("TEST", lowerHalf);
}
VisionResult PointLaneDetector::getResult() {
	return VisionResult();
}