#include "LaneDetector.h"


class LaneDetector
{
	LaneDetector() {

	}
	virtual void calculateFrame() = 0;
	virtual VisionResult getResult() = 0;
};