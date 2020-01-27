#pragma once
#include <vision/lane_detection/VisionResult.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <map>
#include <string>
class PointLaneDetector
{
public:
	PointLaneDetector(std::map<std::string, std::string>&);
	void calculateFrame(cv::Mat&);

	//Ergebnis (alle Spurpunkte)
	VisionResult vRes;
	//Alle erkannten Punkte auf den Linien
	
	cv::Mat ipm;
	cv::Mat threshold;
	cv::Mat edge;
	cv::Mat debugImage;

	

private:
	bool calculateAlgorithm();
	void laneMiddlePoints(std::vector<cv::Point>&, cv::Mat, int);
	void calculateSolveMatrix(cv::Point, cv::Mat& , cv::Mat& , int i);
	void doGPUTransform(cv::Mat&);
	void classifyPoints(int line);
	void prepareInterpolation(int);
	void debugDraw(cv::Mat&);
	bool solveClothoide();
	void copyResult();
	bool solveSingleLane(cv::Mat& lane, cv::Mat A, cv::Mat B, int start, int end, bool foundLane);
	

	void clear();

	cv::Size ipmSize;

	int LANE_THRES_MIN = 5;
	int LANE_THRES_MAX = 60;
	int LL_MIN_X = 580;
	int LL_MAX_X = 630;
	int ML_MIN_X = 680;
	int ML_MAX_X = 730;
	int RL_MIN_X = 800;
	int RL_MAX_X = 850;

	//MODELLPARAMETER
	//Grad des Modells (Klothoide)
	const static int grade = 4;
	//Offset vom oberen und unteren Bildrand
	const static int edgeOffset = 1;
	//Anzahl der Detektionslinien
	const static int numberOfLines = 60;

	int stepSize = 0;

	cv::Ptr<cv::cuda::CannyEdgeDetector> canny;

	cv::Mat transformationMat;

	//Aufteilen der Spurklothoide
	cv::Mat leftLane1;
	cv::Mat middleLane1;
	cv::Mat rightLane1;

	cv::Mat leftLane2;
	cv::Mat middleLane2;
	cv::Mat rightLane2;

	cv::cuda::GpuMat imageGPU;
	cv::cuda::GpuMat ipmGPU;
	cv::cuda::GpuMat thresholdGPU;
	cv::cuda::GpuMat edgeGPU;

	

	//Temporaere Variablen
	cv::Mat linePoints;
	std::vector<cv::Point> laneMiddles;

	cv::Mat lA;
	cv::Mat lB;

	cv::Mat rA;
	cv::Mat rB;

	cv::Mat mA;
	cv::Mat mB;

	bool foundLL = false;
	bool foundML = false;
	bool foundRL = false;

	int numberOfLeftPoints = 0;
	int numberOfMiddlePoints = 0;
	int numberOfRightPoints = 0;

	cv::Point leftLaneStartPoint, middleLaneStartPoint, rightLaneStartPoint;

	std::array<double, numberOfLines> leftDistances;
	std::array<double, numberOfLines> middleDistances;
	std::array<double, numberOfLines> rightDistances;

	std::array<int, numberOfLines> leftLineIndices;
	std::array<int, numberOfLines> middleLineIndices;
	std::array<int, numberOfLines> rightLineIndices;

	int intersectionPosL, intersectionPosM, intersectionPosR;

	void doMean(std::array<double, numberOfLines>&);
	void removeFalse(std::array<double, numberOfLines>&);

};