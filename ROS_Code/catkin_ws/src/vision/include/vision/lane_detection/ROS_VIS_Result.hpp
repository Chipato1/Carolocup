#include <array>
#include <vector>
#include <opencv2/core.hpp>

class ROS_VIS_Result {
public:
	double xoff = 0;
	double deltaPhi = 0;
	double c0 = 0;
	double c1 = 0;
	
	bool valid = false;
	bool oppositeLane = false;
};