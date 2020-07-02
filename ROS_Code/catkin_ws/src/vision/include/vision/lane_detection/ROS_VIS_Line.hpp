#pragma once
#include <array>
#include <opencv2/core.hpp>
#include <vision/lane_detection/ROS_VIS_LinePoint.hpp>
#include <vision/lane_detection/ROS_VIS_LaneDetectionConfig.hpp>
constexpr int NUMBER_OF_LINE_POINTS = 60;

class ROS_VIS_Line
{
public:
	static const int numberOfLines = NUMBER_OF_LINE_POINTS;
	std::array<ROS_VIS_LinePoint, NUMBER_OF_LINE_POINTS> points;

	
	ROS_VIS_Line();
	ROS_VIS_Line(ROS_VIS_LaneDetectionConfig&);

	void setConfig(ROS_VIS_LaneDetectionConfig&);

	int startPointSearchWindowXMin;
	int startPointSearchWindowXMax;
	int startPointSearchWindowYMin;
	int startPointSearchWindowYMax;

	bool forceRecalculate;
	bool found;
	bool shouldRecalculate;
	bool needsClosestPoint;
	

	
	int startIndex;

	int lastValidPointIndex;
	double lastValidAngle;

	const static int grade = 4;

	cv::Mat solveMatrixA;
	cv::Mat solveMatrixB;
	cv::Mat solveMatrixX;

	double xOff;
	double deltaPsi;
	double c0;
	double c1;

	bool solved;

	void calculateLineStep(int lineIterator, int linePositionY, std::vector<cv::Point>& laneMiddles);

	void findStartPoint(std::vector<cv::Point>& laneMiddles, int lineIterator);

	bool revalidatePoint(std::vector<cv::Point>& laneMiddles, int lineIterator);
	
	void solve();

	double calcX(cv::Mat, double);

	void debugDraw(cv::Mat, cv::Scalar);

	void applyClosestPoint(ROS_VIS_LinePoint, int lineIterator);

	void recalculateIfNeccessary();

	void reset();

private:
	ROS_VIS_LaneDetectionConfig config;
};

