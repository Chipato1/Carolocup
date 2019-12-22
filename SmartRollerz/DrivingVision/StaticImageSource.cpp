#include "StaticImageSource.h"
#include <opencv2/highgui/highgui.hpp>
StaticImageSource::StaticImageSource(std::string filename) {
	this->image = cv::imread(filename, cv::IMREAD_GRAYSCALE);
}

cv::Mat StaticImageSource::next() {
	return this->image;
}

bool StaticImageSource::hasNext() {
	return false; //todo
}