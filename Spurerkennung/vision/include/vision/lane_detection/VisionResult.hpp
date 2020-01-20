#include <array>
#include <vector>
#include <opencv2/core.hpp>
class VisionResult {
public:
    std::array<std::vector<cv::Point>, 3> lanePoints;
    std::vector<std::vector<cv::Point>> detectedPoints;

    cv::Mat leftLane1;
	cv::Mat middleLane1;
	cv::Mat rightLane1;

	cv::Mat leftLane2;
	cv::Mat middleLane2;
	cv::Mat rightLane2;

    cv::Mat edgeImage;
};