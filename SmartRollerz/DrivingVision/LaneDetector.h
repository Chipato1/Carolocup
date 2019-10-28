#pragma once
#include "VisionResult.h"
#include <opencv2/highgui.hpp>
class LaneDetector
{
	LaneDetector(cv::VideoCapture);
	virtual void calculateFrame() = 0;
	virtual VisionResult getResult() = 0;
};