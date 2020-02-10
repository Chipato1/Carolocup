#include  <vision/startbox_detection/StartboxDetector.hpp>

#include <iostream>
#include <algorithm>
#include <vector>
#include <zbar.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
using namespace zbar;



StartboxDetector::StartboxDetector() {
    qrDecoder = QRCodeDetector();
}

bool StartboxDetector::checkQRCodeOpenCV(cv::Mat inputImage) {
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

bool StartboxDetector::checkQRCode(Mat &im, vector<decodedObject>&decodedObjects) {
    // Create zbar scanner
  ImageScanner scanner;

      // disable all
  scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 0);

  // enable qr
  scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);

  // Convert image to grayscale
  Mat imGray = im;

  // Wrap image data in a zbar image
  Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);

  // Scan the image for QRCodes
  int n = scanner.scan(image);

  // Print results
  for(Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
  {
    decodedObject obj;

    obj.type = symbol->get_type_name();
    obj.data = symbol->get_data();

    // Print type and data
    cout << "Type : " << obj.type << endl;
    cout << "Data : " << obj.data << endl << endl;
    decodedObjects.push_back(obj);
  }
return false;
}

       
