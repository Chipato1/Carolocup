//Reference:https://www.learnopencv.com/opencv-qr-code-scanner-c-and-python/

#include <vision/startbox_detection/StartboxDetector.hpp>


using namespace std;
using namespace cv;
using namespace zbar;



// Find and decode barcodes and QR codes
void StartboxDetector::decode(Mat& im, vector<decodedObject>& decodedObjects)
{

    // Create zbar scanner
    ImageScanner scanner;

    // disable all
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 0);

    // enable qr
    scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);

    // Convert image to grayscale
    Mat imGray;
    //cvtColor(im, imGray, COLOR_BGR2GRAY);
    imGray = im;
    // Wrap image data in a zbar image
    Image image(im.cols, im.rows, "Y800", (uchar*)imGray.data, im.cols * im.rows);

    // Scan the image for barcodes and QRCodes
    int n = scanner.scan(image);

    // Print results
    for (Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
    {
        decodedObject obj;

        obj.type = symbol->get_type_name();
        obj.data = symbol->get_data();

        // Print type and data
        cout << "Type : " << obj.type << endl;
        cout << "Data : " << obj.data << endl << endl;
        decodedObjects.push_back(obj);
    }
}

void StartboxDetector::checkQRCode(cv::Mat inputImage)
{


    // Variable for decoded objects
    vector<decodedObject> decodedObjects;

    // Find and decode barcodes and QR codes
    decode(inputImage, decodedObjects);

    //return true;
}