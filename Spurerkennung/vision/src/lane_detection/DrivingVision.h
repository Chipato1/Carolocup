#pragma once
#include "VisionResult.h"
#include "LaneDetector.h"

//Main file for DrivingVision Lib
namespace dv {
	class DrivingVision {
	public:
		DrivingVision(std::map<std::string, std::string>&);
		VisionResult doLaneDetection(cv::Mat&);
		LaneDetector* getDetector();

	private:
		std::map<std::string, std::string> config;
		LaneDetector* detector;
	};
}