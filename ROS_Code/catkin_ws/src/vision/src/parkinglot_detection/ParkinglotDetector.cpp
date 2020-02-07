#include  <vision/parkinglot_detection/ParkinglotDetector.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <chrono>
#include <include/vision/parkinglot_detection/ParkinglotDetector.hpp>

using namespace cv;
using namespace std;

double ipmScaling;
double imgHeight = 2400; 



 cv::Mat  ParkinglotDetector:: blankimage() {
    //cv::Mat blankImage;
    cv::Mat blankImage = Mat(roiHeight, roiWidth, CV_8UC3, Scalar(0, 0, 0));
    return blankImage;
}





void ParkinglotDetector :: failure(string i)
{
    cout << "Failed due to: " << i << endl;
}





 void ParkinglotDetector :: drawLines(vector<Vec4i> lines, String txt, int r, int b, int g) {

    cv::Mat line_image = blankimage();

    for (size_t i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];
        line(line_image, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(b, g, r), 3, LINE_AA);
    }

    imshow(txt, line_image);
}





 void ParkinglotDetector:: getPossibleLines(vector<Vec4i>& detectedLines, vector<Vec4i>& possible_lines, int Angle1, int Angle2) {
    Vec4i l;
    Point p1, p2;
    float angle;

    for (size_t i = 0; i < detectedLines.size(); i++)
    {
        l = detectedLines[i];
        p1 = Point(l[0], l[1]);
        p2 = Point(l[2], l[3]); {}

        //calculate angle in radian,  if you need it in degrees just do angle * 180 / PI
        angle = atan2(abs(p1.y - p2.y), abs(p1.x - p2.x)) * (180 / CV_PI);

        if (angle >= Angle1 && angle <= Angle2) {
            possible_lines.push_back(detectedLines.at(i));
        }
    }
}





 void ParkinglotDetector :: getPossibleLineDistance(vector<Vec4i>& detectedLines, vector<Vec4i>& possible_lines, int Distance1, int Distance2)
{
    Vec4i l;
    Point p1, p2;
    float distance;

    for (size_t i = 0; i < detectedLines.size(); i++)
    {
        l = detectedLines[i];
        p1 = Point(l[0], l[1]);
        p2 = Point(l[2], l[3]);

        //calculate distance 
        distance = abs(p1.y - p2.y);

        if (distance >= Distance1 && distance <= Distance2) {
            possible_lines.push_back(detectedLines.at(i));
        }
    }
}






  void ParkinglotDetector :: getPossibleParkingLines(vector<Vec4i>& stopLines, vector<Vec4i>& verticalLines, vector<Vec4i>& resultLines) {
    Vec4i p, m;
    Point p1, p2, m1, m2;

    m = stopLines[0];
    m1 = Point(m[0], m[1]);
    m2 = Point(m[2], m[3]); {}

    for (size_t i = 0; i < verticalLines.size(); i++)
    {
        p = verticalLines[i];
        p1 = Point(p[0], p[1]);
        p2 = Point(p[2], p[3]); {}

        if ((abs(m2.y) >= abs(p2.y) || abs(m2.y) >= abs(p1.y)) && // lines above
            (abs(m1.x - 70) <= abs(p2.x) || abs(m1.x - 10) <= abs(p1.x))) { //lines after
            resultLines.push_back(verticalLines.at(i));
        }
    }
}

  



  double  getParkingLotStartingPosition_Y(vector<Vec4i>& stopLines)
  {
      if (stopLines.empty())
      {
          failure("can not open image");
          return -1;
      }
      Vec4i p, m;
      Point p1, p2, m1, m2;

      m = stopLines[0];
      p = stopLines[1];
      m1 = Point(m[2], m[3]);
      m2 = Point(p[2], p[3]);

      if (m1.y > m2.y)
      {
          return m1.y;
      }
      else
          return m2.y;



  }






double StoplineDetector::getDistanceBetweenPoints(Point p1, Point p2) {
    return abs(cv::norm(p1 - p2));
}





ParkinglotDetector::ParkinglotDetector() {

}





double ParkinglotDetector::detectParkinglots(vector<Vec4i> hough_lines, std::map<std::string, std::string> config) {
    cv::Mat dst, original_img, gray_img, blur_gray_img, canny_img;
    vector<Vec4i> canny_lines, possible_stop_lines, possible_vertical_lines, result_lines, result_lines_300;

    ipmScaling = config.count("ipm_scaling") ? stod(config["ipm_scaling"]);
 	
    if (hough_lines.empty())
    {
        failure("no lines");
        return -1;
    }

 	
    getPossibleLines(hough_lines, result_lines, 45 - 0, 60 + 0);
    
    double parkinglotStartingPoint_y = getParkingLotStartingPosition_Y(result_lines);
    if (parkinglotStartingPoint_y == -1)
    {
        return -1;
        cout << "Parkinglot not found" << endl;
    }
    double distance = (imgHeight - parkinglotStartingPoint_y) / ipmScaling;

    return distance;

    
}