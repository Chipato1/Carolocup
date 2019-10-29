#include "VideoImageSource.h"

VideoImageSource::VideoImageSource(std::string filename) {
	this->capture = cv::VideoCapture(filename);
}

cv::Mat VideoImageSource::next() {
	if (!this->capture.open(0))
		return cv::Mat();
	cv::Mat frame;
	this->capture >> frame;
	return frame;
}

bool VideoImageSource::hasNext() {
	return true; //todo
}