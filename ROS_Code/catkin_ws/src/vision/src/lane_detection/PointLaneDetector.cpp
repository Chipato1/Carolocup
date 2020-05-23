#include <vision/lane_detection/PointLaneDetector.hpp>

#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>

#include <opencv2/highgui.hpp>

#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
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

PointLaneDetector::PointLaneDetector(ROS_VIS_LaneDetectionConfig* cfgObject) {
	this->vRes = ROS_VIS_LaneDetectionResult();
	this->config = *cfgObject;

	this->linePoints = cv::Mat::zeros(1, 25, CV_64F);
	this->laneMiddles.reserve(25);

	this->canny = cuda::createCannyEdgeDetector(config.cannyLowThreshold, config.cannyHighThreshold, config.cannyApertureSize, false);
	this->hough = cuda::createHoughSegmentDetector(1.0f, (float) (CV_PI / 180.0f),50, 5);

	this->undistort = cv::Mat::zeros(this->config.cameraImageSize, CV_64F);
	this->ipm = cv::Mat::zeros(this->config.ipmImageSize, CV_64F);
	this->threshold = cv::Mat::zeros(this->config.ipmImageSize, CV_64F);
	this->edge = cv::Mat::zeros(this->config.ipmImageSize, CV_64F);
	this->debugImage = cv::Mat::zeros(this->config.ipmImageSize, CV_64F);

	this->leftLine.setConfig(this->config);
	this->leftLine.startPointSearchWindowXMin = config.ML_MIN_X;
	this->leftLine.startPointSearchWindowXMax = config.ML_MAX_X;
	this->leftLine.startPointSearchWindowYMin = config.ML_MIN_Y;
	this->leftLine.startPointSearchWindowYMax = config.ML_MAX_Y;

	this->rightLine.setConfig(this->config);
	this->rightLine.startPointSearchWindowXMin = config.RL_MIN_X;
	this->rightLine.startPointSearchWindowXMax = config.RL_MAX_X;
	this->rightLine.startPointSearchWindowYMin = config.RL_MIN_Y;
	this->rightLine.startPointSearchWindowYMax = config.RL_MAX_Y;

	myfile.open("F:\\test2.csv");
}

void PointLaneDetector::setConfig(ROS_VIS_LaneDetectionConfig* cfg)
{
	this->config = *cfg;
}

//Detectes the driving lanes for one frame
void PointLaneDetector::calculateFrame(cv::Mat& frame) {
	if (!frame.empty()) {
		this->doGPUTransform(frame);		
		//this->managePoints();
		//this->solveClothoide();
		//cv::cvtColor(edge, debugImage, cv::COLOR_GRAY2BGR);
		//leftLine.debugDraw(debugImage, cv::Scalar(0, 0, 255));
		//rightLine.debugDraw(debugImage, cv::Scalar(0, 255, 0));
	}
}

void PointLaneDetector::doGPUTransform(cv::Mat& frame) {
	auto t1 = std::chrono::high_resolution_clock::now();
	
	

	this->imageGPU.upload(frame);

	this->calculateIPM();
	
	this->thresholding();

	this->canny->detect(this->thresholdGPU, this->edgeGPU);
	this->edgeGPU.download(edge);

	auto t2 = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	std::cout << duration << std::endl;
	myfile << duration;
	myfile << std::endl;

	//Hough Transformation 
	/*houghZumutung.lock();
	this->hough->detect(this->edgeGPU, this->houghLinesGPU, stream);
	this->stream.enqueueHostCallback(&PointLaneDetector::houghStreamCb, this);
	houghZumutung.unlock();*/
}

void PointLaneDetector::calculateIPM()
{
	cv::cuda::remap(this->imageGPU, this->undistortGPU, this->config.map1GPU, this->config.map2GPU, cv::INTER_NEAREST, cv::BORDER_CONSTANT, std::numeric_limits<float>::quiet_NaN());
	this->undistortGPU.download(this->undistort);

	cv::cuda::warpPerspective(this->undistortGPU, this->ipmGPU, this->config.ipmTransformationMatrix, this->config.ipmImageSize, INTER_CUBIC | WARP_INVERSE_MAP);
	this->ipmGPU.download(this->ipm);
}

void PointLaneDetector::thresholding()
{
	switch (this->config.thresholdingMode)
	{
	case 0:
		cv::cuda::threshold(this->ipmGPU, this->thresholdGPU, this->config.thresholding, 255, cv::THRESH_BINARY);
		this->thresholdGPU.download(this->threshold);
		break;

	case 1:
		if (this->config.otsuThresholdingRefreshCounter >= this->config.otsuThresholdingRefreshMaximum) {
			this->config.thresholding = cv::threshold(ipm, this->threshold, 0, 255, THRESH_OTSU) + 50;
			this->thresholdGPU.upload(this->threshold);
			this->config.otsuThresholdingRefreshCounter = 0;
		}
		else {
			cv::cuda::threshold(this->ipmGPU, this->thresholdGPU, this->config.thresholding, 255, cv::THRESH_BINARY);
			this->thresholdGPU.download(this->threshold);
		}
		this->config.otsuThresholdingRefreshCounter++;
		break;
	default:
		cv::cuda::threshold(this->ipmGPU, this->thresholdGPU, this->config.thresholding, 255, cv::THRESH_BINARY);
		this->thresholdGPU.download(this->threshold);
		break;
	}
}

void PointLaneDetector::houghStreamCb(int status, void *userData) {
	PointLaneDetector *self = static_cast<PointLaneDetector *>(userData);
	std::lock_guard<std::mutex> lk(self->houghMutex);
	self->condition.notify_one();
}



void PointLaneDetector::managePoints() {
	this->clear();
	stepSize = (this->edge.rows - edgeOffset) / (numberOfLines - 1);
	int lineY = this->edge.rows - 2;											//Offset wegen Canny (Bildrand schwarz)
	
	for (int i = 0; i < this->numberOfLines; i++) {
		cv::findNonZero(this->edge.row(lineY), this->linePoints);
		this->laneMiddlePoints(this->laneMiddles, this->linePoints, lineY);
		this->vRes.detectedPoints.push_back(this->laneMiddles);

		std::cout << "[LEFT]";
		this->leftLine.calculateLineStep(i, lineY, this->laneMiddles);
		std::cout << "[RIGH]";
		this->rightLine.calculateLineStep(i, lineY, this->laneMiddles);
		if (leftLine.needsClosestPoint || rightLine.needsClosestPoint) {
			cv::Point lastLeftPoint = leftLine.points.at(leftLine.lastValidPointIndex);
			cv::Point lastRightPoint = rightLine.points.at(rightLine.lastValidPointIndex);

			std::vector<double> distancesLeft;
			distancesLeft.reserve(laneMiddles.size());

			std::vector<double> distancesRight;
			distancesRight.reserve(laneMiddles.size());

			bool nl = leftLine.needsClosestPoint;
			bool nr = rightLine.needsClosestPoint;

			std::for_each(laneMiddles.begin(), laneMiddles.end(),
				[&distancesLeft, &distancesRight, lastLeftPoint, lastRightPoint, nl, nr](cv::Point pt) -> void {
					if (nl) {
						distancesLeft.push_back(cv::norm(pt - lastLeftPoint));
					}
					if (nr) {
						distancesRight.push_back(cv::norm(pt - lastRightPoint));
					}
				}
			);
			std::vector<double>::iterator leftIterator = std::min_element(distancesLeft.begin(), distancesLeft.end());
			int leftIndex = leftIterator - distancesLeft.begin();

			std::vector<double>::iterator rightIterator = std::min_element(distancesRight.begin(), distancesRight.end());
			int rightIndex = rightIterator - distancesRight.begin();

			if (nl && nr && leftIndex == rightIndex && !distancesLeft.empty() && !distancesRight.empty()) {
				std::cout << "[INFO][LINE: " << i << "]: CONFLICT: DL: " << *leftIterator << " vs DR: " << *rightIterator << std::endl;
				if (*leftIterator < *rightIterator) {
					std::cout << "[LEFT]";
					leftLine.applyClosestPoint(ROS_VIS_LinePoint(laneMiddles.at(leftIndex)), i);
				}
				else {
					std::cout << "[RIGH]";
					rightLine.applyClosestPoint(ROS_VIS_LinePoint(laneMiddles.at(rightIndex)), i);
				}
			}
			else {
				if (nl && !distancesLeft.empty()) {
					std::cout << "[LEFT]";
					leftLine.applyClosestPoint(ROS_VIS_LinePoint(laneMiddles.at(leftIndex)), i);
				}
				if (nr && !distancesRight.empty()) {
					std::cout << "[RIGH]";
					rightLine.applyClosestPoint(ROS_VIS_LinePoint(laneMiddles.at(rightIndex)), i);
				}
			}
		}
		lineY -= stepSize;
	}
}

void PointLaneDetector::laneMiddlePoints(std::vector<cv::Point>& laneMiddles, Mat linePoints, int yPos) {
	laneMiddles.clear();
	for (int i = 1; i < linePoints.total(); i++) {
		Point pt1 = linePoints.at<cv::Point>(i - 1);
		Point pt2 = linePoints.at<cv::Point>(i);
		int diff = pt2.x - pt1.x;
		if (diff <= config.LANE_THRES_MAX && diff >= config.LANE_THRES_MIN) {
			Point middle;
			middle.x = pt1.x + diff / 2;
			middle.y = pt1.y + (pt2.y - pt1.y) / 2 + yPos;
			if (!(middle.x > config.ignoreXMin && middle.x <= config.ignoreXMax && middle.y > config.ignoreYMin && middle.y <= config.ignoreYMax)) {
				if ((int)threshold.at<uchar>(middle) == 255) {
					laneMiddles.push_back(middle);
				}
			}
		}
	}
}


void PointLaneDetector::solveClothoide() {
	leftLine.solve();
	rightLine.solve();
	copyResult();
}

void PointLaneDetector::mat2Arr(cv::Mat& mat, std::array<double, 4>& arr) {
	arr.at(0) = mat.at<double>(0) * config.ipmScaling * config.ipmScaling;
	arr.at(1) = mat.at<double>(1) * config.ipmScaling;
	arr.at(2) = mat.at<double>(2);
	arr.at(3) = mat.at<double>(3) / config.ipmScaling;
}

void PointLaneDetector::copyResult() {
	//mat2Arr(this->leftLine.solveMatrixX, this->vRes.leftLane1);
	//mat2Arr(this->rightLine.solveMatrixX, this->vRes.middleLane1);
	//mat2Arr(this->rightLine.solveMatrixX, this->vRes.rightLane1);	
}

void PointLaneDetector::clear() {
	this->linePoints.release();

	this->laneMiddles.clear();
	this->laneMiddles.reserve(25);
}


