#include "PointLaneDetector.h"

#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;
using namespace cv::cuda;

PointLaneDetector::PointLaneDetector() {

}
void PointLaneDetector::calculateFrame(cv::Mat frame) {
	cuda::GpuMat lineMatrixGpu(frame);
	cuda::GpuMat lineMatrixGreyGpu;
	cuda::cvtColor(lineMatrixGpu, lineMatrixGreyGpu, COLOR_BGR2GRAY);
	cuda::GpuMat lineMatrixCannyGpu;
	Ptr<cuda::CannyEdgeDetector> canny = cuda::createCannyEdgeDetector(700, 200, 3);
	canny->detect(lineMatrixGreyGpu, lineMatrixCannyGpu);

	

	Mat download;
	Mat lineMatrix;
	lineMatrixCannyGpu.download(lineMatrix);
	Rect halfSize = Rect(0, lineMatrix.rows / 2, lineMatrix.cols, lineMatrix.rows/2);
	Mat lowerHalf = lineMatrix(halfSize);
	cv::Size scaleSize = cv::Size(lowerHalf.cols, 5);
	cv::resize(lowerHalf, download, scaleSize);
	Mat linePoints;
	cv::findNonZero(download, linePoints);

	for (int i = 0; i < linePoints.total(); i++) {
		//std::cout << "Zero#" << i << ": " << linePoints.at<cv::Point>(i).x << ", " << linePoints.at<cv::Point>(i).y << std::endl;
		Point pt = linePoints.at<cv::Point>(i);
		pt.y = pt.y * 1080/8.5;
		circle(lowerHalf, pt, 5, Scalar(255, 255, 255));
	}
	imshow("scale", lowerHalf);
}
VisionResult PointLaneDetector::getResult() {
	return VisionResult();
}