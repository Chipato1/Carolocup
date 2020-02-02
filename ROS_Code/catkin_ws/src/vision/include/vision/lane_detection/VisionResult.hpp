#include <array>
#include <vector>
#include <opencv2/core.hpp>

enum ERROR_TYPES {
	SUCCESS, ERROR
};


class VisionResult {
public:
    std::array<std::vector<cv::Point>, 3> lanePoints;
    std::vector<std::vector<cv::Point>> detectedPoints;

    std::array<double, 4> leftLane1;
	std::array<double, 4> middleLane1;
	std::array<double, 4> rightLane1;

	std::array<double, 4> leftLane2;
	std::array<double, 4> middleLane2;
	std::array<double, 4> rightLane2;

	bool foundLL = false;
	bool foundML = false;
	bool foundRL = false;

	bool solvedLL1 = false;
	bool solvedML1 = false;
	bool solvedRL1 = false;

	bool solvedLL2 = false;
	bool solvedML2 = false;
	bool solvedRL2 = false;
	
	bool oppositeLane = false;

	double clothoideCutDistanceL_mm;
	double clothoideCutDistanceM_mm;
	double clothoideCutDistanceR_mm;

	ERROR_TYPES state;
};