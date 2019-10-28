#pragma once
#include "LaneDetector.h"
class PointLaneDetector :
	public LaneDetector
{
public:
	PointLaneDetector();
	virtual void calculateFrame(cv::Mat) override;
	virtual VisionResult getResult() override;
};

