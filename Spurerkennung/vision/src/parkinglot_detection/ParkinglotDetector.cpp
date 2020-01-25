#include  <vision/parkinglot_detection/ParkinglotDetector.hpp>

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

const int parkingStartAngle = 45;
const int parkingEndAngle = 60;
const int parkingAngleTreshold = 10;

const int parkingWidth = 300;
const int parkingWidthTreshold = 10;

// TBD
// Image size
// Sample of the image and image vector
// Can you assume lines have 1 pixel wide, if not how to convert to 1 pixel
// bool ParkinglotDetector::checkForParkinglots() Correct?
// If position,  is the position with respect to the image or to something else?
// Why two Vector parameters and are they the same image
// 
ParkinglotDetector::parkinglotDetector() {
	//Init
}

bool ParkinglotDetector::checkForParkinglots() {

	int Angle = 0;
	int Distance = 0;

	Angle = checkAngleBetweenTwoLines(line1, line2);
	if (Angle != 0)
	{
		if ((Angle > parkingStartAngle + parkingAngleTreshold) &&
			(Angle > parkingEndAngle + parkingAngleTreshold)) {

			Distance = checkDistanceBetweenTwoLines(line1, line2);
			if ((Distance > parkingWidth + parkingWidthTreshold) &&
				(Distance > parkingWidth - parkingWidthTreshold)) {
				return true;
			}
		}
	}
	return false;
}

int ParkinglotDetector::checkAngleBetweenTwoLines(vector<Vec4i> line1, vector<Vec4i> line2) {
	Vec4i l, p;
	int x1, x2, x3, x4;
	int y1, y2, y3, y4;
	float angle;

	l = line1[0];
	x1 = l[0];
	y1 = l[1];
	x2 = l[2];
	y2 = l[3];

	p = line2[0];
	x3 = p[0];
	y3 = p[1];
	x4 = p[2];
	y4 = p[3];

	angle = abs(atan2(y2 - y1, x2 - x1) - atan2(y4 - y3, x4 - x3));
	angle = angle * 180 / CV_PI;
	return angle;
}

int ParkinglotDetector::checkDistanceBetweenTwoLines(vector<Vec4i> line1, vector<Vec4i> line2) {
	Vec4i l1, l2;
	int x1, x2, x3, x4;
	int y1, y2, y3, y4;

	l1 = line1[0];
	x1 = l1[0];
	y1 = l1[1];
	x2 = l1[2];
	y2 = l1[3];

	l2 = line2[0];
	x3 = l2[0];
	y3 = l2[1];
	x4 = l2[2];
	y4 = l2[3];

	if ((y2 - y1) == (y4 - y3)) { // If lines are parallel
		return (y2 - y1);
	}
	else {
		return 0;
		
	}
}

int main(int argc, char* argv[]) {

	return 0;
}