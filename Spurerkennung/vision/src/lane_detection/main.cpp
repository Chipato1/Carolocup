#include <iostream>
#include "DrivingVision.h"
#include "PointLaneDetector.h";

int main() {
	dv::DrivingVision drivingVision;
	for (;;) {
		drivingVision.doLaneDetection();
		PointLaneDetector* detector = (PointLaneDetector*) drivingVision.getDetector();
		//detector->detectedPoints;
		//detector->getResult;

		//Aus den erkannten Punkten die Parkplatzlinie erkennen
		//Aus der Hough Transformation https://docs.opencv.org/4.1.0/d9/db0/tutorial_hough_lines.html

	}
	getchar();
	return 0;
}