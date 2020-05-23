#pragma once
#include <map>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/core/cuda.hpp>
class ROS_VIS_LaneDetectionConfig
{
public:
	ROS_VIS_LaneDetectionConfig();
	ROS_VIS_LaneDetectionConfig(std::map<std::string, std::string>&);

	cv::Size cameraImageSize;
	

	cv::Size ipmImageSize;
	double ipmScaling = 1;
	cv::Mat ipmTransformationMatrix;

	int thresholdingMode = 0;
	int thresholding = 128;
	int otsuThresholdingRefreshCounter = 0;
	int otsuThresholdingRefreshMaximum = 100;
	int otsuThresholdingCorrectionFactor = 50;

	double cannyLowThreshold = 0.0;
	double cannyHighThreshold = 0.0;
	double cannyApertureSize = 0.0;

	int LANE_THRES_MIN = 5;
	int LANE_THRES_MAX = 60;
	int LL_MIN_X = 580;
	int LL_MAX_X = 630;
	int ML_MIN_X = 680;
	int ML_MAX_X = 730;
	int RL_MIN_X = 800;
	int RL_MAX_X = 850;

	int LL_MIN_Y = 1500;
	int LL_MAX_Y = 2000;
	int ML_MIN_Y = 1800;
	int ML_MAX_Y = 2400;
	int RL_MIN_Y = 1800;
	int RL_MAX_Y = 2400;

	int ignoreXMin = 450;
	int ignoreXMax = 750;
	int ignoreYMax = 2400;
	int ignoreYMin = 2300;

	cv::cuda::GpuMat map1GPU;
	cv::cuda::GpuMat map2GPU;

	double imToReX(int x);
	int reToImX(double x);
	double imToReY(int y);
	int reToImY(double y);

private:
	
	
};

