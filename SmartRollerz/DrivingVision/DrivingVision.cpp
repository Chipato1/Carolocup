#include "DrivingVision.h"
#include "PointLaneDetector.h"
#include "StaticImageSource.h"
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
	DrivingVision::DrivingVision() {
		this->detector = new PointLaneDetector();
        //this->startDetector = new StartDetection();
		//Initialize GPU context -> Performance
		cv::cuda::GpuMat test;
		test.create(1, 1, CV_8U); // Just to initialize context
	}

	VisionResult DrivingVision::doLaneDetection() {
		

		ImageSource* source = new StaticImageSource("C:\\images\\Parkplatz_Testbild.png");
		cv::Mat matrix = source->next();
		cv::imshow("source", matrix);
		type2str(matrix.type());
		this->detector->calculateFrame(source->next());
		matrix.release();
		cv::waitKey(100);
		return this->detector->getResult();
	}

	bool DrivingVision::doQRCodeDetection() {
		ImageSource* source = new StaticImageSource("C:\\Users\\Maximilian\\source\\repos\\Carolocup\\SmartRollerz\\x64\\Debug\\gerade_1.jpg");
        cv::Mat matrix = source->next();
		//return this->startDetector->checkQRCode(matrix);
		return false;
	}
}
