#include <vision\lane_detection\ROS_VIS_Line.hpp>

#include <iostream>
#include <algorithm>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

ROS_VIS_Line::ROS_VIS_Line()
{
	startIndex = 0;
	found = false;
	solved = false;
	forceRecalculate = false;
	shouldRecalculate = false;
	needsClosestPoint = false;

	startPointSearchWindowXMin = 0;
	startPointSearchWindowXMax = 0;
	startPointSearchWindowYMin = 0;
	startPointSearchWindowYMax = 0;

	lastValidPointIndex = -1;
	lastValidAngle = -1;

	solveMatrixA = cv::Mat::zeros(numberOfLines, grade, CV_64F);
	solveMatrixB = cv::Mat::zeros(numberOfLines, 1, CV_64F);
	solveMatrixX = cv::Mat::zeros(grade, 1, CV_64F);
}


ROS_VIS_Line::ROS_VIS_Line(ROS_VIS_LaneDetectionConfig& cfg) : ROS_VIS_Line() {
	this->setConfig(cfg);
}

void ROS_VIS_Line::setConfig(ROS_VIS_LaneDetectionConfig& cfg)
{
	this->config = cfg;
}

#define SEARCH_WINDOW_WIDTH 20

void ROS_VIS_Line::calculateLineStep(int lineIterator, int linePositionY, std::vector<cv::Point>& laneMiddles)
{
	this->needsClosestPoint = false;
	if (laneMiddles.size() == 0) {
		std::cout << "[LINE: " << lineIterator << "]: Returning because no points found" << std::endl;
		this->needsClosestPoint = false;
		this->points.at(lineIterator).invalidate();
		return;
	}
	ROS_VIS_LinePoint startPoint = points.at(startIndex);
	if (startPoint.valid) {
		std::cout << "[LINE: " << lineIterator << "]: Calc. pt: ";
		if (lineIterator < startIndex) {
			std::cout << "Line Index smaller than old index. Doing nothing" << std::endl;
			//Nix machen
		} else if (lineIterator == startIndex) {
			//Startpunkt validieren
			bool validationSuccess = false;
			std::cout << "Try revalidating start point " << points.at(lineIterator) << ": ";
			if (points.at(lineIterator).valid) {
				validationSuccess = this->revalidatePoint(laneMiddles, lineIterator);
			}
			if (!validationSuccess) {
				//Fatal error: Start point lost: Recalculate line. 
				std::cout << " error" << std::endl;
				this->shouldRecalculate = true;
			}
			else {
				std::cout << " Success" << std::endl;
				lastValidPointIndex = lineIterator;
			}
			
		}
		else {
			//Andere Punkte validieren
			bool validationSuccess = false;
			std::cout <<" try revalidating point " << points.at(lineIterator) <<": ";
			if (points.at(lineIterator).valid) {
				validationSuccess = this->revalidatePoint(laneMiddles, lineIterator);
			}
			if (!validationSuccess) {
				//Finde auf Basis von Abstandsmethode
				std::cout << " Fail. Needs classification." << std::endl;
				needsClosestPoint = true;
				points.at(lineIterator).invalidate();
				//this->findBestFittingPoint(laneMiddles, lineIterator);
				
			}
			else {
				std::cout << " Success" << std::endl;
			}
		}
	}
	else {
		//Reset & Recalculate everything
		std::cout << "No valid start point...";
		this->found = false;
		this->needsClosestPoint = false;
		bool validationSuccess = false;
		if (points.at(lineIterator).valid) {
			validationSuccess = this->revalidatePoint(laneMiddles, lineIterator);
		}

		if (validationSuccess) {
			std::cout << "Found line by revalidating!: Point: " << this->points.at(lineIterator).x << "  " << this->points.at(lineIterator).y << std::endl;
			startIndex = lineIterator;
			lastValidPointIndex = startIndex;
		}
		else {
			this->findStartPoint(laneMiddles, lineIterator);
		}
	}
}

void ROS_VIS_Line::findStartPoint(std::vector<cv::Point>& laneMiddles, int lineIterator)
{
	ROS_VIS_LinePoint* ptToAdd = nullptr;
	auto i = laneMiddles.begin();
	std::cout << "[LINE: " << lineIterator << "]: ";
	while (i != laneMiddles.end()) {
		
		cv::Point analysisPoint = *i;
		if (analysisPoint.x > this->startPointSearchWindowXMin && analysisPoint.x < this->startPointSearchWindowXMax && analysisPoint.y >= this->startPointSearchWindowYMin && analysisPoint.y < this->startPointSearchWindowYMax) {
			ptToAdd = new ROS_VIS_LinePoint(*i);
			laneMiddles.erase(i);
			break;
		}
		++i;
	}

	if (ptToAdd != nullptr) {
		this->points.at(lineIterator) = *ptToAdd;
		this->found = true;
		std::cout << "Found line!: Point: " << this->points.at(lineIterator).x << "  " << this->points.at(lineIterator).y << std::endl;
		startIndex = lineIterator;
		lastValidPointIndex = startIndex;
		delete ptToAdd;
	}
	else {
		std::cout << "No start point found!: " << std::endl;
	}
}

bool ROS_VIS_Line::revalidatePoint(std::vector<cv::Point>& laneMiddles, int lineIterator)
{
	ROS_VIS_LinePoint point = points.at(lineIterator);

	std::vector<double> distances;
	distances.reserve(laneMiddles.size());

	std::for_each(laneMiddles.begin(), laneMiddles.end(),
		[&distances, point](cv::Point pt) -> void {
			double dst = cv::norm(pt - point);
			distances.push_back(dst);
		}
	);
	if (distances.size() > 0) {
		std::vector<double>::iterator minimumDistance = std::min_element(distances.begin(), distances.end());
		int index = minimumDistance - distances.begin();
		if (index != -1 && *minimumDistance <= SEARCH_WINDOW_WIDTH / 2) {
			std::cout << "Revalidated: " << (laneMiddles.at(index)) << " with " << points.at(lineIterator);
			points.at(lineIterator) = ROS_VIS_LinePoint(laneMiddles.at(index));
			laneMiddles.erase(laneMiddles.begin() + index);
			
			if (lastValidPointIndex != startIndex) {
				cv::Point lastPoint = points.at(lastValidPointIndex);
				double dx = ((double)points.at(lineIterator).x - (double)lastPoint.x);
				double dy = ((double)points.at(lineIterator).y - (double)lastPoint.y);
				lastValidAngle = atan(dy / dx);
			}
			else {
				lastValidAngle = 0;
			}
			lastValidPointIndex = lineIterator;
			std::cout << " Angle: " << lastValidAngle;
			return true;
		}
		else {
			points.at(lineIterator).invalidate();
			return false;
		}
	}
	else {
		points.at(lineIterator).invalidate();
		return false;
	}
}

void ROS_VIS_Line::solve()
{
	int matrixCounter = 0;

	std::for_each(points.begin(), points.end(), [this, &matrixCounter](ROS_VIS_LinePoint pt) -> void {
		if (pt.valid) {
			cv::Point point;
			point.y = config.imToReY(pt.y);
			point.x = config.imToReX(pt.x);

			this->solveMatrixA.at<double>(matrixCounter, 0) = (double)point.y * (double)point.y * (double)point.y;
			this->solveMatrixA.at<double>(matrixCounter, 1) = (double)point.y * (double)point.y;
			this->solveMatrixA.at<double>(matrixCounter, 2) = point.y;
			this->solveMatrixA.at<double>(matrixCounter, 3) = 1;
			this->solveMatrixB.at<double>(matrixCounter, 0) = point.x;
			matrixCounter++;
		}
		});

	int start = 0;
	int end = matrixCounter;

	for (int i = matrixCounter; i < numberOfLines; i++) {
		this->solveMatrixA.at<double>(matrixCounter, 0) = 0;
		this->solveMatrixA.at<double>(matrixCounter, 1) = 0;
		this->solveMatrixA.at<double>(matrixCounter, 2) = 0;
		this->solveMatrixA.at<double>(matrixCounter, 3) = 0;
		this->solveMatrixB.at<double>(matrixCounter, 0) = 0;
	}

	

	std::cout << "Found " << matrixCounter << " Points on line" << std::endl;

	if (!found || end - start < grade) {
		solved = false;
		forceRecalculate = true;
		return;
	}

	//std::cout << solveMatrixA << std::endl;
	//std::cout << solveMatrixB << std::endl;

	cv::Range rowRange = cv::Range(start, end);
	cv::Range colRange = cv::Range(0, this->grade);
	cv::Range zeroOneRange = cv::Range(0, 1);
	bool success = cv::solve(solveMatrixA(rowRange, colRange), solveMatrixB(rowRange, zeroOneRange), solveMatrixX, cv::DECOMP_QR);

	//According to the formula
	solveMatrixX.at<double>(0) = solveMatrixX.at<double>(0) * 6;
	solveMatrixX.at<double>(1) = solveMatrixX.at<double>(1) * 2;

	//Remove scaling from the equation
	c1 = solveMatrixX.at<double>(0) * config.ipmScaling * config.ipmScaling;
	c0 = solveMatrixX.at<double>(1) * config.ipmScaling;
	deltaPsi = atan(solveMatrixX.at<double>(2));
	xOff = solveMatrixX.at<double>(3) / config.ipmScaling;

	solved = true;
}

double ROS_VIS_Line::calcX(cv::Mat func, double y) {
	double h1 = func.at<double>(0, 0) / 6;
	double h2 = h1 * y;
	double h3 = h2 * y;
	double h4 = h3 * y;

	double z1 = func.at<double>(1, 0) / 2;
	double z2 = z1 * y;
	double z3 = z2 * y;

	double e1 = func.at<double>(2, 0);
	double e2 = e1 * y;

	double n1 = func.at<double>(3, 0);

	double result = h4 + z3 + e2 + n1;

	return result;
}

void ROS_VIS_Line::debugDraw(cv::Mat im, cv::Scalar color)
{
	for (int ptIterator = 0; ptIterator < this->points.size(); ptIterator++) {
		if (this->points.at(ptIterator).valid) {
			cv::circle(im, this->points.at(ptIterator), 5, color);
			cv::Point pt1 = this->points.at(ptIterator);
			cv::Point pt2 = this->points.at(ptIterator);
			pt1.x -= 30;
			pt2.x += 30;
			//cv::line(im, pt1, pt2, cv::Scalar(128, 128, 128), 3);
		}
	}
	if (!this->solved)
		return;
	int intersect = numberOfLines; //TODO
	for (int row = im.rows - 1; row >= 0; row--) {
		float val = 0;
		int tY = config.imToReY(row + 1);
		int tX = 0;
		if (tY <= intersect) {
			val = calcX(solveMatrixX, tY);
		}
		else {
			val = calcX(solveMatrixX, tY);
		}
		tX = config.reToImX(val);
		if (tX <= im.cols - 1 && tX >= 0) {
			circle(im, (cv::Point(tX, row)), 1, color);
		}
	}
}

void ROS_VIS_Line::applyClosestPoint(ROS_VIS_LinePoint pt, int lineIterator)
{
	if (pt.valid) {
		cv::Point lastPoint = points.at(lastValidPointIndex);
		double dx = ((double)pt.x - (double)lastPoint.x);
		double dy = ((double)pt.y - (double)lastPoint.y);
		double dGes = sqrt(dx * dx + dy * dy);
		double angle = atan(dy / dx);

		double angleDiff = 0.0;
		if (lastValidPointIndex != startIndex) {
			angleDiff = abs(lastValidAngle - angle);
		}
		else {
			std::cout << "[LINE: " << lineIterator << "]: Last valid point is start, angle not existing" << std::endl;
			angleDiff = 0;
		}

		bool nearPointClause = (dGes < 300 && (angleDiff < 0.3 || angleDiff > 2.841592));
		bool farPointClause = (dGes >= 300 && (angleDiff < 0.2 || angleDiff > 2.941592));

		std::cout << "[LINE: " << lineIterator << "]: Try adding point " << pt << " with distance " << dGes << " and angle difference" << angleDiff * 180 / 3.1415;

		if (nearPointClause || farPointClause) {
			std::cout << "...YES!" << std::endl;
			lastValidPointIndex = lineIterator;
			lastValidAngle = angle;
			points.at(lineIterator) = pt;
		}
		else {
			std::cout << "...NO!" << std::endl;
			points.at(lineIterator).invalidate();
		}
	}
	
	
}

void ROS_VIS_Line::recalculateIfNeccessary()
{
	if (this->forceRecalculate) {
		std::cout << "Force Calc: Resetting";
		this->reset();
		this->forceRecalculate = false;
	}
}

void ROS_VIS_Line::reset()
{
	this->found = false;
	this->solved = false;
	this->shouldRecalculate = false;
	this->needsClosestPoint = false;
	lastValidPointIndex = -1;
	this->points.fill(ROS_VIS_LinePoint());

}
