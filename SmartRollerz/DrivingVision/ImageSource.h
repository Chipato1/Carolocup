#pragma once
#include <opencv2/core/core.hpp>

class ImageSource
{
public:
	virtual cv::Mat next() = 0;
	virtual bool hasNext() = 0;
};

