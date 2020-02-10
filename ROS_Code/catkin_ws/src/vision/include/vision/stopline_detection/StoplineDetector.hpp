#pragma once
#include <vision/HoughPoints.h>
#include <vision/HoughPointsArray.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <chrono>

using namespace cv;
using namespace std;

class StoplineDetector
{
public:
    double detect(const vision::HoughPointsArray::ConstPtr &imageArray, int pointerSize, std::map<std::string, std::string> config);
    double getDistanceBetweenPoints(Point p1, Point p2);
    vector<Vec4i> getPossibleEventLine(vector<Vec4i> & detectedLines);
    vector<Vec4i> checkLineWidth (vector<Vec4i> lines);
    cv::Mat defineROI (cv::Mat &image);
    Vec4i getStopLine (vector<Vec4i> lines);
    vector<Vec4i> checkOrthogonal(vector<Vec4i> lines, vector<Vec4i> pLines);
    bool lineIsWithinArea(Vec4i line, Point carCenter);
    
    //Debug Function
    void failureReport(string i);
    void drawLine(vector<Vec4i> lines);
    

};
