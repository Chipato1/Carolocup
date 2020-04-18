#include <vision/lane_detection/PointLaneDetector.hpp>

#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudaarithm.hpp>

#include <opencv2/calib3d.hpp>

#include <iostream>
#include <chrono>



#define _USE_MATH_DEFINES
#include <math.h>
#include <numeric>



using namespace cv;
using namespace cv::cuda;

void drawResult(cv::Mat im, cv::Mat x1, cv::Mat x2, cv::Scalar color, int intersect);

void tester(int status, void* userData) {
	std::cout << "TEST";
}

PointLaneDetector::PointLaneDetector(ROS_VIS_LaneDetectionConfig* cfgObject) {
	this->vRes = ROS_VIS_LaneDetectionResult();
	this->config = *cfgObject;

	this->leftLane1				= cv::Mat::zeros(this->grade, 1, CV_64F);
	this->middleLane1			= cv::Mat::zeros(this->grade, 1, CV_64F);
	this->rightLane1			= cv::Mat::zeros(this->grade, 1, CV_64F);

	this->leftLane2				= cv::Mat::zeros(this->grade, 1, CV_64F);
	this->middleLane2			= cv::Mat::zeros(this->grade, 1, CV_64F);
	this->rightLane2			= cv::Mat::zeros(this->grade, 1, CV_64F);

	this->lA					= cv::Mat::zeros(numberOfLines, grade, CV_64F);
	this->lB					= cv::Mat::zeros(numberOfLines, 1, CV_64F);

	this->mA					= cv::Mat::zeros(numberOfLines, grade, CV_64F);
	this->mB					= cv::Mat::zeros(numberOfLines, 1, CV_64F);

	this->rA					= cv::Mat::zeros(numberOfLines, grade, CV_64F);
	this->rB					= cv::Mat::zeros(numberOfLines, 1, CV_64F);

	this->linePoints 			= cv::Mat::zeros(1, 25, CV_64F);

	this->vRes.detectedPoints.reserve(numberOfLines);
	this->laneMiddles.reserve(25);

	this->canny = cuda::createCannyEdgeDetector(config.cannyLowThreshold, config.cannyHighThreshold, config.cannyApertureSize, false);
	this->hough = cuda::createHoughSegmentDetector(1.0f, (float) (CV_PI / 180.0f),50, 5);

	this->undistort = cv::Mat::zeros(this->config.cameraImageSize, CV_64F);
	this->ipm = cv::Mat::zeros(this->config.ipmImageSize, CV_64F);
	this->threshold = cv::Mat::zeros(this->config.ipmImageSize, CV_64F);
	this->edge = cv::Mat::zeros(this->config.ipmImageSize, CV_64F);
	this->debugImage = cv::Mat::zeros(this->config.ipmImageSize, CV_64F);
}

void printLane(cv::Mat& frame, std::array <double, 4> lane, std::string prefix, cv::Point pos) {
	std::string t1 = prefix + " Winkel: " + std::to_string(atan(lane[2]) * 180 / 3.1415) + " Grad";
	std::string t2 = prefix + " Delta: " + std::to_string(lane[3]) + " mm";
}

void PointLaneDetector::debugDraw(cv::Mat& frame) {
	cv::cvtColor(frame, this->debugImage, COLOR_GRAY2BGR);
	
	if (vRes.solvedLL1) {
		printLane(this->debugImage, this->vRes.leftLane1, "Links", cv::Point(100, 100));
		drawResult(this->debugImage, this->leftLane1, this->leftLane2, Scalar(255, 0, 0), this->vRes.clothoideCutDistanceL_mm);
	}

	if (vRes.solvedML1) {
		printLane(this->debugImage, this->vRes.middleLane1, "Mitte", cv::Point(100, 300));
		drawResult(this->debugImage, this->middleLane1, this->middleLane2, Scalar(255, 255, 255), this->vRes.clothoideCutDistanceM_mm);
	}

	if (vRes.solvedRL1) {
		printLane(this->debugImage, this->vRes.rightLane1, "Rechts", cv::Point(100, 500));
		drawResult(this->debugImage, this->rightLane1, this->rightLane2, Scalar(0, 0, 255), this->vRes.clothoideCutDistanceR_mm);
	}
	

	for (int x = 0; x < this->vRes.lanePoints.size(); x++) {
		for (int y = 0; y < this->vRes.lanePoints.at(x).size(); y++) {
			
			circle(this->debugImage, this->vRes.lanePoints.at(x).at(y), 5, Scalar(x * 128, 255, 255));
		}
	}
}

double calcX(cv::Mat func, double y) {
	double d1 = func.at<double>(0, 0) / 6;
	double d2 = d1 * y;
	double d3 = d2 * y;
	double d4 = d3 * y;

	double z1 = func.at<double>(1, 0) / 2;
	double z2 = z1 * y;
	double z3 = z2 * y;

	double e1 = func.at<double>(2, 0);
	double e2 = e1 * y;

	double n1 = func.at<double>(3, 0);

	double ergebnis = d4 + z3 + e2 + n1;

	return ergebnis;
}

void PointLaneDetector::drawResult(cv::Mat im, cv::Mat x1, cv::Mat x2, cv::Scalar color, double intersect) {
	for (int row = im.rows - 1; row >= 0 ; row--) {
		float val = 0;
		int tY = imToReY(row + 1);
		int tX = 0;
		if (tY <= intersect) {
			val = calcX(x1, tY);
		}
		else {
			val = calcX(x2, tY);
		}
		tX = reToImX(val);
		if (tX <= im.cols - 1 && tX >= 0) {
			circle(im, (cv::Point(tX, row)), 1, color);
		}
	}
}

//Detectes the driving lanes for one frame
void PointLaneDetector::calculateFrame(cv::Mat& frame) {
	if (!frame.empty()) {
		this->doGPUTransform(frame);		
		this->calculateAlgorithm();
		this->debugDraw(this->edge);
	}
}


void PointLaneDetector::doGPUTransform(cv::Mat& frame) {
	this->imageGPU.upload(frame);

	this->calculateIPM();
	
	this->thresholding();

	this->canny->detect(this->thresholdGPU, this->edgeGPU);
	this->edgeGPU.download(edge);

	//Hough Transformation 
	/*houghZumutung.lock();
	this->hough->detect(this->edgeGPU, this->houghLinesGPU, stream);
	this->stream.enqueueHostCallback(&PointLaneDetector::houghStreamCb, this);
	houghZumutung.unlock();*/
}

void PointLaneDetector::calculateIPM()
{
	cv::cuda::remap(this->imageGPU, this->undistortGPU, this->config.map1GPU, this->config.map2GPU, cv::INTER_NEAREST, cv::BORDER_CONSTANT, std::numeric_limits<float>::quiet_NaN());
	this->undistortGPU.download(this->undistort);

	cv::cuda::warpPerspective(this->undistortGPU, this->ipmGPU, this->config.ipmTransformationMatrix, this->config.ipmImageSize, INTER_CUBIC | WARP_INVERSE_MAP);
	this->ipmGPU.download(this->ipm);
}

void PointLaneDetector::thresholding()
{
	switch (this->config.thresholdingMode)
	{
	case 0:
		cv::cuda::threshold(this->ipmGPU, this->thresholdGPU, this->config.thresholding, 255, cv::THRESH_BINARY);
		this->thresholdGPU.download(this->threshold);
		break;

	case 1:
		if (this->config.otsuThresholdingRefreshCounter >= this->config.otsuThresholdingRefreshMaximum) {
			this->config.thresholding = cv::threshold(ipm, this->threshold, 0, 255, THRESH_OTSU) + 50;
			this->thresholdGPU.upload(this->threshold);
			this->config.otsuThresholdingRefreshCounter = 0;
		}
		else {
			cv::cuda::threshold(this->ipmGPU, this->thresholdGPU, this->config.thresholding, 255, cv::THRESH_BINARY);
			this->thresholdGPU.download(this->threshold);
		}
		this->config.otsuThresholdingRefreshCounter++;
		break;
	default:
		cv::cuda::threshold(this->ipmGPU, this->thresholdGPU, this->config.thresholding, 255, cv::THRESH_BINARY);
		this->thresholdGPU.download(this->threshold);
		break;
	}
}

void PointLaneDetector::houghStreamCb(int status, void *userData) {
	PointLaneDetector *self = static_cast<PointLaneDetector *>(userData);
	std::lock_guard<std::mutex> lk(self->houghMutex);
	self->condition.notify_one();
}

void PointLaneDetector::setConfig(ROS_VIS_LaneDetectionConfig * cfg)
{
	this->config = *cfg;
}

void PointLaneDetector::calculateAlgorithm() {
	this->clear();
	stepSize = (this->edge.rows - edgeOffset) / (numberOfLines - 1);
	int lineY = this->edge.rows - 2;											//1: Offset wegen Canny (letzte Zeile schwarz)
	
	this->foundLL = false;
	this->foundML = false;
	this->foundRL = false;

	this->numberOfLeftPoints = 0;
	this->numberOfMiddlePoints = 0;
	this->numberOfRightPoints = 0;

	for (int i = 0; i < this->numberOfLines; i++) {
		cv::findNonZero(this->edge.row(lineY), this->linePoints);
		this->laneMiddlePoints(this->laneMiddles, this->linePoints, lineY);
		this->vRes.detectedPoints.push_back(this->laneMiddles);

		this->prepareInterpolation(i);
		this->classifyPoints(i);

		lineY -= stepSize;
	}
	this->solveClothoide();
}

void PointLaneDetector::clear() {
	this->vRes.lanePoints.at(0).clear();
	this->vRes.lanePoints.at(0).reserve(numberOfLines);
	this->vRes.lanePoints.at(1).clear();
	this->vRes.lanePoints.at(1).reserve(numberOfLines);
	this->vRes.lanePoints.at(2).clear();
	this->vRes.lanePoints.at(2).reserve(numberOfLines);

	this->vRes.detectedPoints.clear();
	this->vRes.detectedPoints.reserve(numberOfLines);

	this->linePoints.release();

	this->laneMiddles.clear();
	this->laneMiddles.reserve(25);

	leftIndex = -1;
	middleIndex = -1;
	rightIndex = -1;

	oldLeftRel = -1;
	oldMiddleRel = -1;
	oldRIghtRel = -1;
}



double PointLaneDetector::imToReX(int x)
{
	return ((double)x - config.ipmImageSize.width / 2);
}

int PointLaneDetector::reToImX(double x)
{
	return (int)(x + config.ipmImageSize.width / 2);
}

double PointLaneDetector::imToReY(int y)
{
	return (-(double)y + config.ipmImageSize.height);
}

int PointLaneDetector::reToImY(double y)
{
	return (int)(-y + config.ipmImageSize.height);
}

void PointLaneDetector::classifyPoints(int line) {
	if (!laneMiddles.empty() && (!foundLL || !foundML || !foundRL)) {
		for (int pointI = 0; pointI < laneMiddles.size(); pointI++) {
			cv::Point analysisPoint = laneMiddles.at(pointI);
			if (pointI == leftIndex || pointI == middleIndex || pointI == rightIndex) {
				continue;
			}

			if (analysisPoint.x > config.LL_MIN_X&& analysisPoint.x < config.LL_MAX_X && analysisPoint.y >= config.LL_MIN_Y && analysisPoint.y < config.LL_MAX_Y) {
				if (!foundLL) {
					foundLL = true;
					leftLaneStartPoint = analysisPoint;
					vRes.lanePoints.at(0).push_back(analysisPoint);
					calculateSolveMatrix(analysisPoint, lA, lB, numberOfLeftPoints);
					laneMiddles.erase(laneMiddles.begin() + pointI);
					this->leftDistances[line] = 1;
					lastLeftIterator = line;
					numberOfLeftPoints++;
				}
			}
			else if (analysisPoint.x > config.ML_MIN_X&& analysisPoint.x < config.ML_MAX_X && analysisPoint.y >= config.ML_MIN_Y && analysisPoint.y < config.ML_MAX_Y) {
				if (!foundML) {
					foundML = true;
					middleLaneStartPoint = analysisPoint;
					vRes.lanePoints.at(1).push_back(analysisPoint);
					calculateSolveMatrix(analysisPoint, mA, mB, numberOfMiddlePoints);
					laneMiddles.erase(laneMiddles.begin() + pointI);
					this->middleDistances[line] = 1;
					lastMiddleIterator = line;
					numberOfMiddlePoints++;
				}
			}
			else if (analysisPoint.x > config.RL_MIN_X&& analysisPoint.x < config.RL_MAX_X && analysisPoint.y >= config.RL_MIN_Y && analysisPoint.y < config.RL_MAX_Y) {
				if (!foundRL) {
					foundRL = true;
					rightLaneStartPoint = analysisPoint;
					vRes.lanePoints.at(2).push_back(analysisPoint);
					calculateSolveMatrix(analysisPoint, rA, rB, numberOfRightPoints);
					laneMiddles.erase(laneMiddles.begin() + pointI);
					this->rightDistances[line] = 1;
					lastRightIterator = line;
					numberOfRightPoints++;
				}
			}
		}
	}
}

void PointLaneDetector::prepareInterpolation(int i) {
	if (!laneMiddles.empty() && (foundLL || foundML || foundRL)) {
		std::vector<double> distancesLeft;
		distancesLeft.reserve(laneMiddles.size());

		std::vector<double> distancesMiddle;
		distancesMiddle.reserve(laneMiddles.size());

		std::vector<double> distancesRight;
		distancesRight.reserve(laneMiddles.size());

		std::for_each(laneMiddles.begin(), laneMiddles.end(),
			[this, &distancesLeft, &distancesMiddle, &distancesRight](cv::Point pt) -> void {
				distancesLeft.push_back(cv::norm(pt - this->leftLaneStartPoint));
				distancesMiddle.push_back(cv::norm(pt - this->middleLaneStartPoint));
				distancesRight.push_back(cv::norm(pt - this->rightLaneStartPoint));
			}
		);
		std::vector<double>::iterator iteratorLeft = std::min_element(distancesLeft.begin(), distancesLeft.end());
		this->leftIndex = iteratorLeft - distancesLeft.begin();
		std::vector<double>::iterator iteratorMiddle = std::min_element(distancesMiddle.begin(), distancesMiddle.end());
		this->middleIndex = iteratorMiddle - distancesMiddle.begin();
		std::vector<double>::iterator iteratorRight = std::min_element(distancesRight.begin(), distancesRight.end());
		this->rightIndex = iteratorRight - distancesRight.begin();



		if (foundLL && foundML && leftIndex == middleIndex) {
			if (*iteratorLeft <= *iteratorMiddle) {
				middleIndex = -1;
			}
			else {
				leftIndex = -1;
			}
		}
		if (foundLL && foundRL && leftIndex == rightIndex) {
			if (*iteratorLeft <= *iteratorRight) {
				rightIndex = -1;
			}
			else {
				leftIndex = -1;
			}
		}

		if (foundML && foundRL && middleIndex == rightIndex) {
			if (*iteratorMiddle <= *iteratorRight) {
				rightIndex = -1;
			}
			else {
				middleIndex = -1;
			}
		}

		



		if (foundLL && leftIndex >= 0 && distancesLeft.at(leftIndex) < 420) {
			int dx = laneMiddles.at(leftIndex).x - this->leftLaneStartPoint.x;
			int dy = laneMiddles.at(leftIndex).y - this->leftLaneStartPoint.y;
			double temp = (double)i - (double)lastLeftIterator;
			double rel = abs(oldLeftRel - (dx / dy));
			if (oldLeftRel < 0 || rel < 0.3) {
				lastLeftIterator = i;
				vRes.lanePoints.at(0).push_back(laneMiddles.at(leftIndex));
				calculateSolveMatrix(laneMiddles.at(leftIndex), lA, lB, numberOfLeftPoints);
				leftLaneStartPoint = laneMiddles.at(leftIndex);
				oldLeftRel = (dx / dy);
				numberOfLeftPoints++;
			}			
		}
		else {
			leftIndex = -1;
		}

		if (foundML && middleIndex >= 0) {
			double dx = ((double)laneMiddles.at(middleIndex).x - (double)this->middleLaneStartPoint.x);
			double dy = ((double)laneMiddles.at(middleIndex).y - (double)this->middleLaneStartPoint.y);
			double rel = oldMiddleRel - (dx / dy);

			if ((numberOfMiddlePoints == 1 || (*iteratorMiddle < 300 && rel < 0.3 && rel > -0.3) || (*iteratorMiddle >= 300 && rel < 0.15 && rel > -0.15))
) {
				lastMiddleIterator = i;
				vRes.lanePoints.at(1).push_back(laneMiddles.at(middleIndex));
				calculateSolveMatrix(laneMiddles.at(middleIndex), mA, mB, numberOfMiddlePoints);
				middleLaneStartPoint = laneMiddles.at(middleIndex);
				
				numberOfMiddlePoints++;
				oldMiddleRel = (dx / dy);
				
			}
		}
		else {
			middleIndex = -1;
		}
		if (foundRL && rightIndex >= 0) {
			double dx = ((double)laneMiddles.at(rightIndex).x - (double)this->rightLaneStartPoint.x);
			double dy = ((double)laneMiddles.at(rightIndex).y - (double)this->rightLaneStartPoint.y);
			double rel = oldRIghtRel - (dx / dy);
			if ((numberOfRightPoints == 1 || (*iteratorRight < 300 && rel < 0.3 && rel > -0.3) || (*iteratorRight >= 300 && rel < 0.15 && rel > -0.15))) {
				lastRightIterator = i;
				vRes.lanePoints.at(2).push_back(laneMiddles.at(rightIndex));
				calculateSolveMatrix(laneMiddles.at(rightIndex), rA, rB, numberOfRightPoints);
				rightLaneStartPoint = laneMiddles.at(rightIndex);
				oldRIghtRel = (dx / dy);
				numberOfRightPoints++;
			}
		}
		else {
			rightIndex = -1;
		}
	}
}

bool PointLaneDetector::solveSingleLane(cv::Mat& lane, cv::Mat A, cv::Mat B, int start, int end, bool foundLane) {
	if (!foundLane || end - start < grade || end-start < 6) {
		return false;
	}


	Range rowRange = Range(start, end);
	Range colRange = Range(0, this->grade);
	Range zeroOneRange = Range(0, 1);
	bool success = cv::solve(A(rowRange, colRange), B(rowRange, zeroOneRange),lane, DECOMP_QR);
	
	lane.at<double>(0) = lane.at<double>(0) * 6;
	lane.at<double>(1) = lane.at<double>(1) * 2;
	return success;
}

double PointLaneDetector::calculateVariance(cv::Mat& lane,  std::vector<cv::Point> pts) {
	std::vector<double> res(pts.size(), 0);
	std::transform(pts.begin(), pts.end(), res.begin(), [this, lane](cv::Point point)->double{
		point.y = imToReY(point.y);
		point.x = imToReX(point.x);
		return calcX(lane, point.y) - point.x;
	});
	double mean = 0;
	double m2 = 0;
	std::for_each(res.begin(), res.end(), [&mean, &m2](double elem)->void {
		mean+=elem;
		m2+=elem*elem;
	});
	return m2 - mean * mean;
	
}

void PointLaneDetector::solveClothoide() {
	int separationIndexL = 0;
	int separationIndexM = 0;
	int separationIndexR = 0;

	int separationDist = 0;
	/*for(int i = 4; i < numberOfRightPoints && separationIndexR == 0; i+=5) {
		
		if (solveSingleLane(this->rightLane1, this->rA, this->rB, 0, i, foundRL)) {
			double variance = calculateVariance(this->rightLane1, this->vRes.lanePoints[2]);
			//std::cout << variance;
			if (variance > 10) {
				separationIndexR = i;
				separationDist = this->vRes.lanePoints[2].at(separationIndexR).y;
			}
			
		}
	}
	this->vRes.clothoideCutDistanceR_mm = imToReY(separationDist);*/
	

	//Keine Trennung gefunden -> nur C1 ist valide
	separationIndexR = 0;
	if(separationIndexR == 0) {
		separationIndexL = numberOfLeftPoints;
		separationIndexM = numberOfMiddlePoints;
		separationIndexR = numberOfRightPoints;

		this->vRes.clothoideCutDistanceL_mm = imToReY(0);
		this->vRes.clothoideCutDistanceM_mm = imToReY(0);
		this->vRes.clothoideCutDistanceR_mm = imToReY(0);
	} else {
		if(foundLL) {
			auto res = std::find_if(this->vRes.lanePoints[0].begin(), this->vRes.lanePoints[0].end(), [&separationDist](cv::Point& elem) -> bool {
				return elem.y > separationDist;
			});
			this->vRes.clothoideCutDistanceL_mm = imToReY((*res).y);
			separationIndexL = res - this->vRes.lanePoints[0].begin();
		}
		if(foundML) {
			auto res = std::find_if(this->vRes.lanePoints[1].begin(), this->vRes.lanePoints[1].end(), [&separationDist](cv::Point& elem) -> bool {
				return elem.y > separationDist;
			});
			this->vRes.clothoideCutDistanceM_mm = imToReY((*res).y);
			separationIndexM = res - this->vRes.lanePoints[1].begin();
		}
	}

	
	
	if (foundML && foundRL && numberOfLeftPoints < numberOfRightPoints && numberOfMiddlePoints < numberOfRightPoints) {
		vRes.oppositeLane = false;
	}

	if (foundML && foundRL && !foundLL && numberOfMiddlePoints > numberOfRightPoints) {
		vRes.oppositeLane = true;
	} else {
		vRes.oppositeLane = false;
	}

	
	this->vRes.solvedLL1 = solveSingleLane(this->leftLane1, this->lA, this->lB, 0, separationIndexL, foundLL);
	this->vRes.solvedML1 = solveSingleLane(this->middleLane1, this->mA, this->mB, 0, separationIndexM, foundML);
	this->vRes.solvedRL1 = solveSingleLane(this->rightLane1, this->rA, this->rB, 0, separationIndexR, foundRL);

	//std::cout << this->leftLane1;


	//this->vRes.solvedLL2 = solveSingleLane(this->leftLane2, this->lA, this->lB, separationIndexL, numberOfLines, foundLL);
	//this->vRes.solvedML2 = solveSingleLane(this->middleLane2, this->mA, this->mB, separationIndexM, numberOfLines, foundML);
	//this->vRes.solvedRL2 = solveSingleLane(this->rightLane2, this->rA, this->rB, separationIndexR, numberOfLines, foundRL);
	
	//std::cout << this->leftLane2;
	copyResult();
}

void PointLaneDetector::mat2Arr(cv::Mat& mat, std::array<double, 4>& arr) {
	arr.at(0) = mat.at<double>(0) * config.ipmScaling * config.ipmScaling;
	arr.at(1) = mat.at<double>(1) * config.ipmScaling;
	arr.at(2) = mat.at<double>(2);
	arr.at(3) = mat.at<double>(3) / config.ipmScaling;
}

void PointLaneDetector::copyResult() {
	//if (!this->vRes.oppositeLane) {
		mat2Arr(this->leftLane1, this->vRes.leftLane1);
		mat2Arr(this->middleLane1, this->vRes.middleLane1);
		mat2Arr(this->rightLane1, this->vRes.rightLane1);
		mat2Arr(this->leftLane2, this->vRes.leftLane2);
		mat2Arr(this->middleLane2, this->vRes.middleLane2);
		mat2Arr(this->rightLane2, this->vRes.rightLane2);
		vRes.foundLL = foundLL;
		vRes.foundML = foundML;
		vRes.foundRL = foundRL;
	/*} else {
		mat2Arr(this->middleLane1, this->vRes.leftLane1);
		mat2Arr(this->rightLane1, this->vRes.middleLane1);

		mat2Arr(this->middleLane1, this->vRes.leftLane1);
		mat2Arr(this->rightLane1, this->vRes.middleLane1);

		vRes.foundLL = foundML;
		vRes.foundML = foundRL;
		vRes.foundRL = false;

		vRes.solvedLL1 = vRes.solvedML1;
		vRes.solvedML1 = vRes.solvedRL1;
		vRes.solvedRL1 = false;
	
		vRes.solvedLL2 = vRes.solvedML2;
		vRes.solvedML2 = vRes.solvedRL2;
		vRes.solvedRL2 = false;
	}*/
	
}

void PointLaneDetector::laneMiddlePoints(std::vector<cv::Point>& laneMiddles, Mat linePoints, int yPos) {
	laneMiddles.clear();
	for (int i = 1; i < linePoints.total(); i++) {
		Point pt1 = linePoints.at<cv::Point>(i - 1);
		Point pt2 = linePoints.at<cv::Point>(i);
		int diff = pt2.x - pt1.x;
		if (diff <= config.LANE_THRES_MAX && diff >= config.LANE_THRES_MIN) {
			Point middle;
			middle.x = pt1.x + diff / 2;
			middle.y = pt1.y + (pt2.y - pt1.y) / 2 + yPos;
			if (!(middle.x > config.ignoreXMin && middle.x <= config.ignoreXMax && middle.y > config.ignoreYMin&& middle.y <= config.ignoreYMax)) {
				if ((int)threshold.at<uchar>(middle) == 255) {
					laneMiddles.push_back(middle);
				}
			} 
		}
	}
}

void PointLaneDetector::calculateSolveMatrix(Point point, cv::Mat& A, cv::Mat& B, int i) {
	point.y = imToReY(point.y);
	point.x = imToReX(point.x);

	A.at<double>(i, 0) = (double)point.y * (double)point.y * (double)point.y;
	A.at<double>(i, 1) = (double)point.y * (double)point.y;
	A.at<double>(i, 2) = point.y;
	A.at<double>(i, 3) = 1;
	B.at<double>(i, 0) = point.x;
}
