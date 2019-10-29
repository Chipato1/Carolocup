#pragma once
#include "ImageSource.h"
#include <string>
#include <opencv2/core.hpp>
class StaticImageSource :
	public ImageSource
{
public:
	StaticImageSource(std::string);
	virtual cv::Mat next() override;
	virtual bool hasNext() override;

private:
	cv::Mat image;
};

