#include <iostream>
#include "DrivingVision.h"

int main() {
	dv::DrivingVision drivingVision;
	for (;;) {
		drivingVision.doLaneDetection();
	}
	return 0;
}