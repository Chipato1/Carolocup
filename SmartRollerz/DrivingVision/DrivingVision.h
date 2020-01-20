#pragma once
#include "VisionResult.h"
#include "LaneDetector.h"
//Main file for DrivingVision Lib
namespace dv {
	class DrivingVision {
	public:
		DrivingVision();
		VisionResult doLaneDetection();
		bool doQRCodeDetection();

	private:
		LaneDetector* detector;
	};



}