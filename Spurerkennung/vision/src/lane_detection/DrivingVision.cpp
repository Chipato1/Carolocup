#include "DrivingVision.h"
#include "PointLaneDetector.h"
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/highgui.hpp>

std::string type2str(int type) {
	std::string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}

namespace dv {
	DrivingVision::DrivingVision(std::map<std::string, std::string>& config) {
		this->detector = new PointLaneDetector(config);
		this->config = config;

		//Initialize GPU context -> Performance
		cv::cuda::GpuMat test;
		test.create(1, 1, CV_8U);
	}

	VisionResult DrivingVision::doLaneDetection(cv::Mat& image) {
		this->detector->calculateFrame(image);
		return this->detector->getResult();
	}

	LaneDetector* DrivingVision::getDetector()
	{
		return this->detector;
	}
}
