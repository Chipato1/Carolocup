#include "ros/ros.h"
#include "std_msgs/UInt8.h"

/*typedef struct
{
	float a;
	float b;
	float c;
	float d;
} clothoide_t;

typedef struct
{
	clothoide_t trajectory_clothoid;
	clothoide_t path_clothoid;
	float lengthfactor;
} trajectory_t; // todo two clothoides for path

trajectory_t currentTrajectory;
*/
int main(int argc, char **argv)
{
  
	ros::init(argc, argv, "trajektorie");
	ros::NodeHandle nodeHandle;

	ros::Publisher trajektorie_pub = nodeHandle.advertise<std_msgs::UInt8>("deltaY", 10);

	ros::Rate loop_rate(50);

	while (ros::ok())
	{
		std_msgs::UInt8 number;
		number.data = 42;

		ROS_INFO("Starting trajectory calculation");

		trajektorie_pub.publish(number);

		loop_rate.sleep();
	}

	return 0;
}
/*
float clothoideAt(float x, clothoide_t clothoide)
{
	float ret = 0;

	if (x < 1)
	{
		ret = 0 // todo
	}
	else if (x < 2)
	{
		
	}
	else if (x < 3)
	{
		
	}
	else if (x < 4)
	{
		
	}
	
	return ret;
}

float trajectoryAt(float x, trajectory_t trajectory)
{
	return clothoideAt(trajectory->trajectory_clothoid) + clothoideAt(trajectory->path_clothoid);
}

float getMaxSteeringAngle(trajectory_t trajectory)
{
	// todo
}

int generateOvertakingMergeOutTrajectory(trajectory_t *trajectory, float vehicleDistance, float lanewidth, clothoide_t path)
{
	
}

int generateOvertakingMergeBackTrajectory(trajectory_t *trajectory, float requiredDistance, float lanewidth, clothoide_t path)
{
	
}*/
