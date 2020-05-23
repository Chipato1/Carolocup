#pragma once
#include <vision/lane_detection/VisionResult.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <map>
#include <string>
#include <condition_variable>

#include <vision/lane_detection/ROS_VIS_LaneDetectionConfig.hpp>
#include <vision/lane_detection/ROS_VIS_Line.hpp>

#include <iostream>
#include <fstream>

class PointLaneDetector {
public:
	PointLaneDetector(ROS_VIS_LaneDetectionConfig*);
	void calculateFrame(cv::Mat&);
	
	cv::Mat undistort;
	cv::Mat ipm;
	cv::Mat threshold;
	cv::Mat edge;
	cv::Mat debugImage;
	cv::Mat houghLinesCPU;

	std::function <void (std::vector<cv::Vec4i> data)> houghCallback;
	std::mutex houghMutex;
	std::mutex houghZumutung;

	cv::cuda::GpuMat houghLinesGPU;

	cv::cuda::Stream stream;
	std::condition_variable condition;

	void setConfig(ROS_VIS_LaneDetectionConfig* );
	ROS_VIS_LaneDetectionResult vRes;

	std::ofstream myfile;

private:
	PointLaneDetector();
	ROS_VIS_LaneDetectionConfig config;
	

	void managePoints();
	void laneMiddlePoints(std::vector<cv::Point>&, cv::Mat, int);
	void doGPUTransform(cv::Mat&);

	void calculateIPM();
	void thresholding();

	void solveClothoide();
	void copyResult();
	void mat2Arr(cv::Mat&, std::array<double, 4>&);
	static void houghStreamCb(int status, void *userData);
	void clear();
	

	cv::Ptr<cv::cuda::CannyEdgeDetector> canny;
	cv::Ptr<cv::cuda::HoughSegmentDetector> hough;

	cv::cuda::GpuMat imageGPU;
	cv::cuda::GpuMat undistortGPU;
	cv::cuda::GpuMat ipmGPU;
	cv::cuda::GpuMat thresholdGPU;
	cv::cuda::GpuMat edgeGPU;


	//Offset vom oberen und unteren Bildrand
	const static int edgeOffset = 1;

	const static int numberOfLines = 60;

	int stepSize = 0;

	//Temporaere Variablen
	cv::Mat linePoints;
	std::vector<cv::Point> laneMiddles;




	ROS_VIS_Line leftLine;
	ROS_VIS_Line rightLine;
};
