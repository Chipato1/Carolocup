#pragma once
#include <string>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

typedef struct
{
  string type;
  string data;
  vector <Point> location;
}decodedObject;



class StartboxDetector
{
public:
    bool checkQRCode(Mat &im, vector<decodedObject>&decodedObjects);
    bool checkQRCodeOpenCV(cv::Mat inputImage);
    StartboxDetector();
    
private:
    cv::Mat inputImage;
    cv::QRCodeDetector qrDecoder;
    cv::Mat bbox, rectifiedImage;
    std::string extractedData;
    
    const std::string STOP_TEXT = "STOP";
};

