#pragma once
#include "ImageSource.h"
#include <opencv2/highgui.hpp>
class CameraImageSource :
	public ImageSource
{
public:
	CameraImageSource();
	virtual cv::Mat next() override;
	virtual bool hasNext() override;

private:
	cv::VideoCapture capture;
};

