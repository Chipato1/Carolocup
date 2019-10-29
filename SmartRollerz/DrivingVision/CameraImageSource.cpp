#include "CameraImageSource.h"

CameraImageSource::CameraImageSource() {
	this->capture = cv::VideoCapture(0);
}

cv::Mat CameraImageSource::next() {
	if (!this->capture.open(0))
		return cv::Mat();
	cv::Mat frame;
	this->capture >> frame;
	return frame;
}

bool CameraImageSource::hasNext() {
	return true; //todo
}