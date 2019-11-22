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

void PointLaneDetector::calculateFrame(cv::Mat frame) {
	GpuMat upload(frame);
	GpuMat edgeImageGPU = edgeDetection(upload);
	Mat edgeImage(edgeImageGPU);

	Mat* splitImage = halfImage(edgeImage);

	Mat lowerHalf = splitImage[1];
	
	Mat column= lowerHalf.row(lowerHalf.rows - 1 - lowerHalf.rows / 4);

	Mat linePoints;
	cv::findNonZero(column, linePoints);

	for (int i = 0; i < linePoints.total(); i++) {
		//std::cout << "Zero#" << i << ": " << linePoints.at<cv::Point>(i).x << ", " << linePoints.at<cv::Point>(i).y << std::endl;
		Point pt = linePoints.at<cv::Point>(i);
		pt.y = lowerHalf.rows - 1 - lowerHalf.rows / 4;
		circle(lowerHalf, pt, 5, Scalar(255, 255, 255));
	}
	line(lowerHalf, Point(0, lowerHalf.rows - 1 - lowerHalf.rows / 4), Point(lowerHalf.cols, lowerHalf.rows - 1 - lowerHalf.rows / 4), Scalar(255, 255, 255));

	//imshow("TEST", lowerHalf);
	imwrite("C:\\Users\\Maximilian\\source\\repos\\Carolocup\\SmartRollerz\\x64\\Debug\\result_1.jpg", lowerHalf);
	getchar();
}
VisionResult PointLaneDetector::getResult() {
	return VisionResult();
}