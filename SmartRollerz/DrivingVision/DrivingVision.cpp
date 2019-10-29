#include "DrivingVision.h"
#include "PointLaneDetector.h"
#include "StaticImageSource.h"
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/highgui.hpp>

namespace dv {
	DrivingVision::DrivingVision() {
		this->detector = new PointLaneDetector();
	}

	VisionResult DrivingVision::doLaneDetection() {
		ImageSource* source = new StaticImageSource("C:\\Users\\Maximilian\\source\\repos\\Carolocup\\SmartRollerz\\x64\\Debug\\gerade_1.jpg");
		cv::Mat matrix = source->next();
		this->detector->calculateFrame(source->next());
		cv::waitKey(10);
		return this->detector->getResult();
	}
}