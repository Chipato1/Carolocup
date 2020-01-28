#include "ros/ros.h"
#include "std_msgs/UInt8.h"

enum states_e {
	INIT,
	QR_CODE_DETECTED,
	DRIVE
};

struct INIT_data {
   ros::Time begin;
} INIT_data;