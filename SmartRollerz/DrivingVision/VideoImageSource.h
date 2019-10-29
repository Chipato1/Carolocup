#pragma once
#include "ImageSource.h"
#include <string>
#include <opencv2/highgui.hpp>
class VideoImageSource :
	public ImageSource
{
public:
	VideoImageSource(std::string);
	virtual cv::Mat next() override;
	virtual bool hasNext() override;

private:
	cv::VideoCapture capture;
};

