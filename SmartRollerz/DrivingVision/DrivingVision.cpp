#include "DrivingVision.h"
#include "PointLaneDetector.h"
#include <opencv2/core.hpp>

namespace dv {
	DrivingVision::DrivingVision() {
		this->detector = new PointLaneDetector();
	}

	VisionResult DrivingVision::doLaneDetection() {
		cv::Mat frame;	//TBD.
		this->detector->calculateFrame(frame);
		return this->detector->getResult();
	}
}