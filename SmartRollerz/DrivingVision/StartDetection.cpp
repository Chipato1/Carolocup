#include "StartDetection.h"

StartDetection::StartDetection() {
    qrDecoder = QRCodeDetector();
}

bool StartDetection::getQRCode() {
    //TODO: Utile class mit getCurrentImage
    //inputImage = getCurrentImage();
    
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

