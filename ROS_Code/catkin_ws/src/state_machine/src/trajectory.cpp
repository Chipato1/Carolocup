#include "trajectory.h"

/* General */
void trj_init()
{

}

/* Util */
float trj_stdClothoideAt(clothoide_t clothoide, float x)
{
	return 0;
}

float trj_stdCircleAt(float radius, float x)
{
	return 0;
}

/* Overtaking */
int trj_overtake_generateMergeOutTrajectory(unsigned int laneWidth, unsigned int length, clothoide_t curve)
{
	return 0;
}

int trj_overtake_generateMergeBackTrajectory(unsigned int laneWidth, unsigned int length, clothoide_t curve)
{
	return 0;
}

float trj_overtake_getMergeOutSteeringAngleAtDistance(float distance)
{
	return 0;
}

float trj_overtake_getMergeBackSteeringAngleAtDistance(float distance)
{
	return 0;
}

/* Parking */
int trj_park_generateParkingTrajectory(unsigned int laneWidth, unsigned int parkingSpaceLength)
{
	return 0;
}

float trj_park_getParkInLongSteeringAngleAtDistance(float distance)
{
	return 0;
}

float trj_park_getParkOutLongSteeringAngleAtDistance(float distance)
{
	return 0;
}

float trj_park_getParkInSteeringAngleAtDistance(float distance)
{
	return 0;
}

float trj_park_getParkOutSteeringAngleAtDistance(float distance)
{
	return 0;
}

int trj_park_getParkInDirectionAtDistance(float distance)
{
	return 0;
}

int trj_park_getParkOutDirectionAtDistance(float distance)
{
	return 0;
}