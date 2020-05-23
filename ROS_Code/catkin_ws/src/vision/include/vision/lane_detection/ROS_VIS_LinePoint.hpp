#pragma once
#include <opencv2/core.hpp>
class ROS_VIS_LinePoint : public cv::Point
{
public:
	bool valid;
	void invalidate();
	ROS_VIS_LinePoint(cv::Point pt);
	ROS_VIS_LinePoint(int x, int y);
	ROS_VIS_LinePoint();
};

