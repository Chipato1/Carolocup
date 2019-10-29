#pragma once
#include "VisionResult.h"
#include <opencv2/core/core.hpp>
class LaneDetector
{
public:
	virtual void calculateFrame(cv::Mat) = 0;
	virtual VisionResult getResult() = 0;
};