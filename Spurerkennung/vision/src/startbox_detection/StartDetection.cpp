#include  <vision/lane_detection/StartDetection.hpp>

using namespace cv;

StartDetection::StartDetection() {
    qrDecoder = QRCodeDetector();
}

bool StartDetection::checkQRCode(cv::Mat inputImage) {
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

