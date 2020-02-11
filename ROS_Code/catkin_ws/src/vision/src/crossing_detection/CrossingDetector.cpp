#include  <vision/crossing_detection/CrossingDetector.hpp>


using namespace cv;
using namespace std;



CrossingDetector::CrossingDetector(std::map<std::string, std::string> config)
{
	this->ipmSizeX		= config.count("ipm_size_x")	? stod(config["ipm_size_x"])	: 1600;
	this->ipmSizeY		= config.count("ipm_size_y")	? stod(config["ipm_size_y"])	: 2000;
	this->ipmScaling	= config.count("ipm_scaling")	? stod(config["ipm_scaling"])	: 1;
	this->roiCenterX = ipmSizeX * 3/4;
	

	this->validation	= 0;
}

void CrossingDetector::failureReport(string i) {
	cout << "Failed due to: " << i << endl;
}

void CrossingDetector::drawLine(vector<Vec4i> lines) {

	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		//cout << "P1: " << Point(l[0], l[1]) << " p" << Point(l[2], l[3]) << endl;
		line(this->img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}

	imshow("detected lines", this->img);
	waitKey(1);
}

double CrossingDetector::getYDistanceBetweenPoints(Point p1, Point p2) {
	return abs(p1.y - p2.y);
}

//Check if the line is a stopping or perpendicular line
vector<Vec4i> CrossingDetector::getPossibleEventLine(vector<Vec4i>& detectedLines) {
	vector<Vec4i> possibleStoppLine;
	Vec4i l;
	Point p1, p2;
	float angle;

	for (size_t i = 0; i < detectedLines.size(); i++)
	{
		l = detectedLines[i];
		// draw the lines

		p1 = Point(l[0], l[1]);
		p2 = Point(l[2], l[3]);
		//calculate angle in radian,  if you need it in degrees just do angle * 180 / PI
		angle = abs(atan2(p1.y - p2.y, p1.x - p2.x) * (180 / CV_PI));
		//cout << "angle: " <<angle<< endl;
		if (angle > 160 || angle < 20) {
			possibleStoppLine.push_back(detectedLines.at(i));
		}

		if (angle < 100 && angle > 80) {
			perpendicularLines.push_back(detectedLines.at(i));
		}
		//std::cout << "Winkel spur " << i << " : " << angle << std::endl;
	}

	return possibleStoppLine;
}

vector<Vec4i> CrossingDetector::checkLineWidth(vector<Vec4i> lines) {
	Vec4i l1;
	Vec4i l2;
	double distance1;
	double distance2;
	double distance3;
	double distance4;
	vector<Vec4i> resultingLines;
	size_t i = 0;
	Point p1;
	Point p2;
	Point p3;
	Point p4;
	for (size_t q = 0; q < lines.size() - 1; q++) {
		l1 = lines[q];
		p1 = Point(l1[0], l1[1]);
		p2 = Point(l1[2], l1[3]);
		i++;
		for (; i < lines.size(); i++)
		{
			l2 = lines[i];
			p3 = Point(l2[0], l2[1]);
			p4 = Point(l2[2], l2[3]);
			distance1 = getYDistanceBetweenPoints(p1, p3);
			distance2 = getYDistanceBetweenPoints(p1, p4);
			distance3 = getYDistanceBetweenPoints(p2, p3);
			distance4 = getYDistanceBetweenPoints(p2, p4);
			//cout << "d1: " << distance1 << "  d2: " << distance2 << endl;
			if ((distance1 > 20 && distance1 < 100) || (distance2 > 20 && distance2 < 100) || (distance3 > 20 && distance3 < 100) || (distance4 > 20 && distance4 < 100)) {
				resultingLines.push_back(lines[q]);
				resultingLines.push_back(lines[i]);
			}

		}
	}
	//    drawLine(resultingLines);
	return resultingLines;
}

bool CrossingDetector::lineIsWithinArea(Vec4i line, Point carCenter) {
	if ((abs(line[0] - carCenter.x) < 400 && (ipmSizeY - 1500) < line[1]) || (abs(line[2] - carCenter.x) < 400 && (ipmSizeY - 1500) < line[3])) {
		return true;
	}

	return false;
}

Vec4i CrossingDetector::getStopLine(vector<Vec4i> lines) {
	Vec4i i;
	vector<double> distance;

	Vec4i l1;
	Point p1;
	Point p2;
	Point carCenter(roiCenterX, ipmSizeY);


	double distance1;
	double distance2;
	double min = 0;


	Vec4i resultLine;

	resultLine = lines[0];

	if (lines.size() == 1) {
		if (lineIsWithinArea(resultLine, carCenter)) {
			return resultLine;
		}
		else {
			return {};
		}

	}
	else {

		p1 = Point(resultLine[0], resultLine[1]);
		p2 = Point(resultLine[2], resultLine[3]);

		if (getYDistanceBetweenPoints(p1, carCenter) < getYDistanceBetweenPoints(p2, carCenter)) {
			min = getYDistanceBetweenPoints(p1, carCenter);
		}
		else {
			min = getYDistanceBetweenPoints(p2, carCenter);
		}


		for (size_t q = 1; q < lines.size(); q++) {
			l1 = lines[q];
			p1 = Point(l1[0], l1[1]);
			p2 = Point(l1[2], l1[3]);

			distance1 = getYDistanceBetweenPoints(p1, carCenter);
			distance2 = getYDistanceBetweenPoints(p2, carCenter);


			if (distance1 < min && lineIsWithinArea(l1, carCenter)) {
				min = distance1;
				resultLine = l1;
			}
			if (distance2 < min && lineIsWithinArea(l1, carCenter)) {
				min = distance2;
				resultLine = l1;
			}
		}
	}

	//	cout << "Yposition: " << abs(resultLine[1]-roiHeight) << " Xpos: " << abs(resultLine[0]-carCenter.x) <<endl;
	if (lineIsWithinArea(resultLine, carCenter)) {
		return resultLine;
	}
	else {
		return {};
	}
}

vector<Vec4i> CrossingDetector::checkOrthogonal(vector<Vec4i> lines, vector<Vec4i> pLines) {
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
		for (size_t i = 0; i < lines.size(); i++)
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

			angle = abs(atan2(y2 - y1, x2 - x1) - atan2(y4 - y3, x4 - x3));

			angle = (float)angle * 180 / CV_PI;
			//cout << "orth: " << angle << endl;
		//cout << "x1: "  << x1 << " x2: " << x2 << " x3: " << x3 << " x4: " << x4 << endl; 
			if (angle > 80 && angle < 100 && (x1 < x3 || x2 < x4) && (y1 < y3 || y2 < y4)) {
				resultingLines.push_back(lines[i]);
			}

		}
	}

	return resultingLines;
}

double CrossingDetector::calculateDistance(Vec4i stoppLine) {

	return (double)((ipmSizeY - stoppLine[1]) / ipmScaling);
}

int decreaseValidation(int validation) {
	if (validation > 0)
		validation--;

	return validation;
}

//call by reference
double CrossingDetector::detect(vector<Vec4i> lines) {
	//cout << "-----------------------New Message---------------------------------" << endl;
	/*img = cv::Mat(2000, 1600, CV_8UC3, Scalar(0, 0, 0));
	
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}

	line(img, Point(roiCenterX - 400, ipmSizeY), Point(roiCenterX - 400, 0), Scalar(0, 0, 255), 3, LINE_AA);
	line(img, Point(roiCenterX + 400, ipmSizeY), Point(roiCenterX + 400, 0), Scalar(0, 0, 255), 3, LINE_AA);
	line(img, Point(0, 1500), Point(roiCenterX, 1500), Scalar(0, 0, 255), 3, LINE_AA);*/



	/*vector<Vec4i> lines;
	Vec4i l;
	for(int i = 0; i < pointerSize; i++){
		const vision::HoughPoints &data = imageArray->points[i];
		l[0] = data.x1;
		l[1] = data.y1;
		l[2] = data.x2;
		l[3] = data.y2;
		lines.push_back(l);
	} */

	//std::cout << "Detected " << lines.size() << " line(s)" << std::endl;
	if (!lines.empty()) {
		//std::cout << "Suche winkel" << std::endl;
		lines = getPossibleEventLine(lines);
	}
	else {
		failureReport("1");
		//validation = decreaseValidation(validation);
		return -1.0;
	}

	//eigentlich kann man wenn hier nichts gefunden wird sofort abbrechen !
	if (!lines.empty()) {
		lines = checkLineWidth(lines);
	}
	else {
		failureReport("2");
		validation = decreaseValidation(validation);
		return -1.0;
	}

	//    Check if stoppline is orthogonal to perpendicular
	if (!lines.empty()) {
		//lines = checkOrthogonal(lines, perpendicularLines);
	}
	else {
		failureReport("3");
		validation = decreaseValidation(validation);
		return -1.0;
	}

	Vec4i stoppLine;
	if (!lines.empty()) {
		stoppLine = getStopLine(lines);
	}
	else {
		failureReport("4");
		validation = decreaseValidation(validation);
		return -1.0;
	}

	if (stoppLine[0] != 0 && stoppLine[1] != 0 && stoppLine[2] != 0 && stoppLine[3] != 0) {
		validation++;
	}
	else {
		validation = decreaseValidation(validation);
		return -1.0;
	}

	cout << "validation: " << validation << endl;
	if (validation > 2) {
		Vec4i l;
		l = stoppLine;
		//line(img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 255, 255), 3, LINE_AA);
		validation = 0;
		cout << "---------Found Intersection------------" << endl;
		//imshow("te", img);
		return calculateDistance(stoppLine);
	}

	//imshow("te", img);
	//waitKey(0);
	return -1.0;
}
