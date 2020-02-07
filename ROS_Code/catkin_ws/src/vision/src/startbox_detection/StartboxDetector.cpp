#include  <vision/startbox_detection/StartboxDetector.hpp>

using namespace cv;

StartboxDetector::StartboxDetector() {
    qrDecoder = QRCodeDetector();
}

bool StartboxDetector::checkQRCode(cv::Mat inputImage) {
//    cv::resize(inputImage, inputImage, cv::Size(1600,1200));
    cv::threshold(inputImage, inputImage, 70, 255, cv::THRESH_BINARY);
    //Detect and Decode the QRCode in the image
    extractedData = qrDecoder.detectAndDecode(inputImage);
       
    if(extractedData.length()>0)
     {
         if (extractedData.compare(STOP_TEXT)) {
             return true;
         }
     }
    return false;
}

