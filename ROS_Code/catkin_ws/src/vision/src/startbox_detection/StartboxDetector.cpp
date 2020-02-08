#include  <vision/startbox_detection/StartboxDetector.hpp>

using namespace cv;

StartboxDetector::StartboxDetector() {
    qrDecoder = QRCodeDetector();
}

bool StartboxDetector::checkQRCode(cv::Mat inputImage) {
    cv::resize(inputImage, inputImage, cv::Size(800,600));
	cv::Mat outputImage;
    cv::threshold(inputImage, outputImage, 70, 255, cv::THRESH_BINARY);
    //Detect and Decode the QRCode in the image
    extractedData = qrDecoder.detectAndDecode(outputImage);
       
    if(extractedData.length()>0)
     {  
             return true;
     }
    return false;
}

       
