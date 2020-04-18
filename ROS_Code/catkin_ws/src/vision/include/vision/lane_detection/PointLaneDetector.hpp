#pragma once
#include <vision/lane_detection/VisionResult.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <map>
#include <string>
#include <condition_variable>

#include <vision/lane_detection/ROS_VIS_LaneDetectionConfig.hpp>

class PointLaneDetector {
public:
	PointLaneDetector(ROS_VIS_LaneDetectionConfig*);
	void calculateFrame(cv::Mat&);
	
	cv::Mat undistort;
	cv::Mat ipm;
	cv::Mat threshold;
	cv::Mat edge;
	cv::Mat debugImage;
	cv::Mat houghLinesCPU;

	std::function <void (std::vector<cv::Vec4i> data)> houghCallback;
	std::mutex houghMutex;
	std::mutex houghZumutung;

	cv::cuda::GpuMat houghLinesGPU;

	cv::cuda::Stream stream;
	std::condition_variable condition;

	void setConfig(ROS_VIS_LaneDetectionConfig* );
	ROS_VIS_LaneDetectionResult vRes;


private:
	PointLaneDetector();
	ROS_VIS_LaneDetectionConfig config;
	

	void calculateAlgorithm();
	void laneMiddlePoints(std::vector<cv::Point>&, cv::Mat, int);
	void calculateSolveMatrix(cv::Point, cv::Mat& , cv::Mat& , int i);
	void doGPUTransform(cv::Mat&);

	void calculateIPM();
	void thresholding();


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
	

	int leftIndex = -1;
	int middleIndex = -1;
	int rightIndex = -1;

	double oldLeftRel = -1.0;
	double oldMiddleRel = -1.0;
	double oldRIghtRel = -1.0;

	int lastLeftIterator = 0;
	int lastMiddleIterator = 0;
	int lastRightIterator = 0;

	
	
	cv::Ptr<cv::cuda::CannyEdgeDetector> canny;
	cv::Ptr<cv::cuda::HoughSegmentDetector> hough;


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

	//MODELLPARAMETER
//Grad des Modells (Klothoide)
	const static int grade = 4;
	//Offset vom oberen und unteren Bildrand
	const static int edgeOffset = 1;
	//Anzahl der Detektionslinien
	const static int numberOfLines = 60;

	int stepSize = 0;

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
