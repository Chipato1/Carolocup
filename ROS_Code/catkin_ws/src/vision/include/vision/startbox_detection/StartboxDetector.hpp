#pragma once
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <algorithm>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <zbar.h>


using namespace std;
using namespace cv;
using namespace zbar;

typedef struct
{
    string type;
    string data;
    vector <Point> location;
}decodedObject;

class StartboxDetector
{
public:


    void checkQRCode(cv::Mat inputImage);
    void decode(cv::Mat& im, vector<decodedObject>& decodedObjects);
    
private:
    cv::Mat inputImage;
    cv::QRCodeDetector qrDecoder;
    cv::Mat bbox, rectifiedImage;
    std::string extractedData;
    
    const std::string STOP_TEXT = "STOP";
};

