#include <opencv2/highgui/highgui.hpp>
#include "include/opencv4/opencv2/core/core.hpp"
#include "include/opencv4/opencv2/imgproc/imgproc.hpp"
#include "include/opencv4/opencv2/opencv.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <chrono>


using namespace cv;
using namespace std;

float roiHeight;
float roiWidth;
cv::Mat cdst;
vector<Vec4i> perpendicularLines;
vector<Vec4i> possibleStartLine;
bool startingLine = false;


void failure(string i)
{
 cout << "Failed due to: " << i << endl;
}

void drawLine (vector<Vec4i> lines) {
    
    for( size_t i = 0; i < lines.size(); i++ )
      {
          Vec4i l = lines[i];
          cout << "P1: " << Point(l[0], l[1]) << " p" << Point(l[2], l[3]) << endl;
          line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
      }
    
    imshow("detected lines", cdst);
    waitKey();
}

double getDistanceBetweenPoints(Point p1, Point p2) {
    return abs(cv::norm(p1-p2));
}


//Check for line Size -> Am Ende machen
vector<Vec4i> getPossibleEventLine(vector<Vec4i> & detectedLines) {
    vector<Vec4i> possibleStoppLine;
    Vec4i l;
    Point p1, p2;
    float angle;
    
    for( size_t i = 0; i < detectedLines.size(); i++ )
    {
        l = detectedLines[i];
        // draw the lines

        p1=Point(l[0], l[1]);
        p2=Point(l[2], l[3]);
        //calculate angle in radian,  if you need it in degrees just do angle * 180 / PI
        angle = atan2(p1.y - p2.y, p1.x - p2.x) * (180/CV_PI);
        
        if (angle > 171) {
            possibleStoppLine.push_back(detectedLines.at(i));
        }
        
        if (angle < 100 && angle > 80) {
            perpendicularLines.push_back(detectedLines.at(i));
        }
    }
    
    return possibleStoppLine;
}

vector<Vec4i> checkLineWidth (vector<Vec4i> lines) {
    Vec4i l1;
    Vec4i l2;
    double distance1;
    double distance2;
    vector<Vec4i> resultingLines;
    size_t i = 0;
    Point p1;
    Point p2;
    Point p3;
    Point p4;
    for (size_t q = 0; q < lines.size()-1; q++) {
        l1 = lines[q];
        p1 = Point(l1[0], l1[1]);
        i++;
        for(;i < lines.size(); i++ )
          {
              l2 = lines[i];
              p2 = Point(l2[0], l2[1]);
              p3 = Point(l2[2], l2[3]);
              distance1 = getDistanceBetweenPoints(p1, p2);
              distance2 = getDistanceBetweenPoints(p1, p3);

              cout << "d1: " << distance1 << "  d2: " << distance2 << endl;
              if ((distance1 > 50 && distance1 < 200) || (distance2 > 50 && distance2 < 200)) {
                  resultingLines.push_back(lines[q]);
                  resultingLines.push_back(lines[i]);
              }
              
          }
    }
//    drawLine(resultingLines);
    return resultingLines;
}

cv::Mat defineROI (cv::Mat src) {
    roiHeight = 900;
    roiWidth = 300;
    Rect region_of_interest = Rect(1000, 200, 300, 900);
    
    return src(region_of_interest);
}

 Vec4i getStoppLine (vector<Vec4i> lines) {
    Vec4i i;
    vector<double> distance;
    
    Vec4i l1;
    Point p1;
    Point p2;
    Point carCenter(roiWidth/2, roiHeight);
    double distance1;
    double distance2;
    double min = 0;
    
    Vec4i resultLine;
    
    p1 = Point(l1[0], l1[1]);
    min = getDistanceBetweenPoints(p1, carCenter);
    resultLine = lines[0];
    
    for (size_t q = 0; q < lines.size()-1; q++) {
        l1 = lines[q];
        p1 = Point(l1[0], l1[1]);
        p2 = Point(l1[2], l1[3]);
        
        distance1 = getDistanceBetweenPoints(p1, carCenter);
        distance2 = getDistanceBetweenPoints(p2, carCenter);
        
        if (distance1 < min){
            min = distance1;
            resultLine = lines[q];
        }
        else if (distance2 < min) {
            min = distance2;
            resultLine = lines[q];
        }
    }
     
    return resultLine;
}

vector<Vec4i> checkOrthogonal(vector<Vec4i> lines, vector<Vec4i> pLines) {
    vector<Vec4i> resultingLines;
    Vec4i l;
    Vec4i p;
    int m1, m2;
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;

    float angle;
    
    size_t i = 0;
    for (size_t q = 0; q < pLines.size(); q++) {
        p = pLines[q];
        for(size_t i = 0;i < lines.size(); i++ )
        {
            l = lines[i];
            x1 = l[0];
            y1 = l[1];
            x2 = l[2];
            y2 = l[3];
            
            x3 = p[0];
            y3 = p[1];
            x4 = p[2];
            y4 = p[3];
            
            angle = abs(atan2(y2-y1, x2-x1) - atan2(y4-y3,x4-x3));
            
            angle = angle *180/CV_PI;
            cout << "Thetha: " << angle << endl;
            if (angle > 80 && angle < 100) {
                resultingLines.push_back(lines[i]);
            }
        }
    }
    
    return resultingLines;
}

int main(int argc, char* argv[]) {
    
    cv::Mat src = imread("images/startLine.png", 0);
    
    if(src.empty())
    {
        failure("0");
        cout << "can not open " << "Picture" << endl;
        return -1;
    }
    
    
    vector<Point2f> centers;
    Size patternsize(3,5); //number of centers
//    bool patternfound = findChessboardCorners(src,patternsize,centers);
    
    if (patternfound) {
        cout << "found board" << endl;
    }


//    Duration of each component
    std::chrono::time_point<std::chrono::system_clock> startHough, endHough, startIdentifying, endIdentifying;
    
    //Define ROI
    src = defineROI(src);
    
    Mat dst;
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, COLOR_GRAY2BGR);

    vector<Vec4i> lines;
 
//    Hough Transformation
    startHough = std::chrono::system_clock::now();
    HoughLinesP(dst, lines, 1, CV_PI/180, 70, 70, 10 );
    endHough = std::chrono::system_clock::now();

    
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::microseconds>(endHough-startHough).count();
    std::cout << "Hough Transform duration: " << elapsed_seconds << endl;

    
    startIdentifying = std::chrono::system_clock::now();

    
    if (!lines.empty()) {
        lines = getPossibleEventLine(lines);
    }
    else {
           failure("1");
           exit(-1);
    }
    
//    drawLine(lines);
    
    //eigentlich kann man wenn hier nichts gefunden wird sofort abbrechen !
    if (!lines.empty()) {
        lines = checkLineWidth(lines);
    }
    else{
        failure("2");
        exit(-1);
    }
    
//    drawLine(lines);

    
//    Check if stoppline is orthogonal to perpendicular
    lines = checkOrthogonal(lines, perpendicularLines);
    
    Vec4i stoppLine;
    if (!lines.empty()) {
        stoppLine = getStoppLine(lines);
    }
    else{
           failure("3");
           exit(-1);
    }
    

    
//    drawLine(possibleStartLine);
    
    endIdentifying = std::chrono::system_clock::now();
    elapsed_seconds = std::chrono::duration_cast<std::chrono::microseconds>(endIdentifying-startIdentifying).count();
    
    std::cout << "Identifying Lanes duration: " << elapsed_seconds << endl;

    line( cdst, Point(stoppLine[0], stoppLine[1]), Point(stoppLine[2], stoppLine[3]), Scalar(0,0,255), 3, LINE_AA);
    
    imshow("detected lines", cdst);

    waitKey();

    return 0;
}