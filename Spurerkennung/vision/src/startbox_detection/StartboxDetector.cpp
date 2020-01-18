#include  <vision/startbox_detection/StartboxDetector.hpp>

using namespace cv;

StartboxDetector::StartboxDetector() {
    qrDecoder = QRCodeDetector();
}

bool StartboxDetector::checkQRCode(cv::Mat inputImage) {
    //Detect and Decode the QRCode in the image
    extractedData = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);
       
    if(extractedData.length()>0)
     {
         if (extractedData.compare(STOP_TEXT)) {
             return true;
         }
     }
    return false;
}

