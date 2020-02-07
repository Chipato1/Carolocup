#pragma once
#include <opencv2/core/core.hpp>
#include <vision/HoughPointsArray.h>
#include <vision/HoughPoints.h>




class ParkinglotDetector
{
public:
	cv::Mat blankimage();
	void failure(string i);
	void drawLines(vector<Vec4i> lines, String txt, int r, int b, int g);
	void getPossibleLines(vector<Vec4i>& detectedLines, vector<Vec4i>& possible_lines, int Angle1, int Angle2);
	void getPossibleParkingLines(vector<Vec4i>& stopLines, vector<Vec4i>& verticalLines, vector<Vec4i>& resultLines);
	void detectParkinglots();
	double getParkingLotStartingPosition(vector<Vec4i>& stopLines)
	ParkinglotDetector();
	double distanceToStartingPointOfParkinglot(Point startingPiontParkinglotPosition)
};