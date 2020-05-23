#include <vision\lane_detection\ROS_VIS_LinePoint.hpp>

void ROS_VIS_LinePoint::invalidate()
{
	this->valid = false;
	this->x = 0;
	this->y = 0;

}

ROS_VIS_LinePoint::ROS_VIS_LinePoint(cv::Point pt) : cv::Point(pt)
{
	this->valid = true;
}

ROS_VIS_LinePoint::ROS_VIS_LinePoint(int x, int y) : cv::Point(x,y)
{
	this->valid = true;
}

ROS_VIS_LinePoint::ROS_VIS_LinePoint() : cv::Point()
{
	this->valid = false;
}
