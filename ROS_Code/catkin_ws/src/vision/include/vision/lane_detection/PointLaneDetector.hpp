#pragma once
#include <vision/lane_detection/VisionResult.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <map>
#include <string>
#include <condition_variable>
class PointLaneDetector {
public:
	PointLaneDetector(std::map<std::string, std::string>&);
	void calculateFrame(cv::Mat&);

	//Ergebnis (alle Spurpunkte)
	VisionResult vRes;
	//Alle erkannten Punkte auf den Linien
	
	cv::Mat undistort;
	cv::Mat ipm;
	cv::Mat threshold;
	cv::Mat edge;
	cv::Mat debugImage;
	cv::Mat houghLinesCPU;

	
	cv::Mat map1;
	cv::Mat map2;

	double thres_cut;

	std::function <void (std::vector<cv::Vec4i> data)> houghCallback;
	std::mutex houghMutex;
	std::mutex houghZumutung;
	std::mutex otsuLock;

	cv::cuda::GpuMat map1GPU;
	cv::cuda::GpuMat map2GPU;


	cv::cuda::GpuMat houghLinesGPU;

	cv::cuda::Stream stream;
	std::condition_variable condition;

	cv::Size ipmSize;
	
private:
	void calculateAlgorithm();
	void laneMiddlePoints(std::vector<cv::Point>&, cv::Mat, int);
	void calculateSolveMatrix(cv::Point, cv::Mat& , cv::Mat& , int i);
	void doGPUTransform(cv::Mat&);
	void classifyPoints(int line);
	void prepareInterpolation(int);
	void debugDraw(cv::Mat&);
	void solveClothoide();
	void copyResult();
	void mat2Arr(cv::Mat&, std::array<double, 4>&);
	bool solveSingleLane(cv::Mat& lane, cv::Mat A, cv::Mat B, int start, int end, bool foundLane);
	static void houghStreamCb(int status, void *userData);
	double calculateVariance(cv::Mat& lane, std::vector<cv::Point> pts);
	void drawResult(cv::Mat im, cv::Mat x1, cv::Mat x2, cv::Scalar color, double intersect);
	void clear();
	void calculateThreshold(cv::Mat&);
	int thresholdRefreshCounter = 0;
	int thresh_mode = 0;
	int thresh_refresh = 100;
	int thresh_otsu_correction = 50;
	double thresh_target_percentage = 0.05;
	double thresh_target_acc_percentage = 0.005;

	

	int LANE_THRES_MIN = 5;
	int LANE_THRES_MAX = 60;
	int LL_MIN_X = 580;
	int LL_MAX_X = 630;
	int ML_MIN_X = 680;
	int ML_MAX_X = 730;
	int RL_MIN_X = 800;
	int RL_MAX_X = 850;

	int LL_MIN_Y = 1500;
	int LL_MAX_Y = 2000;
	int ML_MIN_Y = 1800;
	int ML_MAX_Y = 2400;
	int RL_MIN_Y = 1800;
	int RL_MAX_Y = 2400;

	int ignoreXMin = 450;
	int ignoreXMax = 750;
	int ignoreYMax = 2400;
	int ignoreYMin = 2300;

	int leftIndex = -1;
	int middleIndex = -1;
	int rightIndex = -1;

	double oldLeftRel = -1.0;
	double oldMiddleRel = -1.0;
	double oldRIghtRel = -1.0;

	int lastLeftIterator = 0;
	int lastMiddleIterator = 0;
	int lastRightIterator = 0;

	double ipmScaling = 1; 
	int ipm_size_x = 1200;
	int ipm_size_y = 2400;

	//MODELLPARAMETER
	//Grad des Modells (Klothoide)
	const static int grade = 4;
	//Offset vom oberen und unteren Bildrand
	const static int edgeOffset = 1;
	//Anzahl der Detektionslinien
	const static int numberOfLines = 60;

	int stepSize = 0;

	cv::Ptr<cv::cuda::CannyEdgeDetector> canny;
	cv::Ptr<cv::cuda::HoughSegmentDetector> hough;

	

	cv::Mat transformationMat;

	//Aufteilen der Spurklothoide
	cv::Mat leftLane1;
	cv::Mat middleLane1;
	cv::Mat rightLane1;

	cv::Mat leftLane2;
	cv::Mat middleLane2;
	cv::Mat rightLane2;

	cv::cuda::GpuMat imageGPU;
	cv::cuda::GpuMat undistortGPU;
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

	double imToReX(int x);
	int reToImX(double x);
	double imToReY(int y);
	int reToImY(double y);

};
