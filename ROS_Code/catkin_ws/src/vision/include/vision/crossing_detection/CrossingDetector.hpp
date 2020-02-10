#pragma once

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

class CrossingDetector
{
public:
    CrossingDetector(std::map<std::string, std::string> config);
    double detect(vector<Vec4i> lines, int pointerSize);

    double getYDistanceBetweenPoints(Point p1, Point p2);
    vector<Vec4i> getPossibleEventLine(vector<Vec4i> & detectedLines);
    vector<Vec4i> checkLineWidth (vector<Vec4i> lines);
    Vec4i getStopLine (vector<Vec4i> lines);
    vector<Vec4i> checkOrthogonal(vector<Vec4i> lines, vector<Vec4i> pLines);
    bool lineIsWithinArea(Vec4i line, Point carCenter);
    double calculateDistance(Vec4i);
    
    //Debug Function
    void failureReport(string i);
    void drawLine(vector<Vec4i> lines);

    double roiCenterX;
    
    vector<Vec4i> perpendicularLines;
    vector<Vec4i> lines;
    
    cv::Mat img;

    //config details
    double ipmScaling;
    double ipmSizeX;
    double ipmSizeY;

    int validation;

};
