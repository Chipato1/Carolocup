#pragma once
#include "LaneDetector.h"
#include <opencv2/core/cuda.hpp>

#include <opencv2/cudaimgproc.hpp>
class PointLaneDetector :
	public LaneDetector
{
public:
	PointLaneDetector();
	virtual void calculateFrame(cv::Mat) override;
	virtual VisionResult getResult() override;

private:
	bool internalCalc(cv::Mat frame, int startLine);
	void laneMiddlePoints(std::vector<cv::Point>&, cv::Mat, int);

	const int grade = 3;
	cv::Mat leftLane;
	cv::Mat middleLane;
	cv::Mat rightLane;
	std::array<std::vector<cv::Point>, 3> result;

	cv::Mat lA;
	cv::Mat lB;

	cv::Mat mA;
	cv::Mat mB;

	cv::Mat rA;
	cv::Mat rB;

	const int edgeOffset = 1;
	const int numberOfLines = 60;

	cv::Ptr<cv::cuda::CannyEdgeDetector> canny;

	cv::Mat transformationMat;
};

