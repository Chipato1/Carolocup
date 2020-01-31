/**
 * trajectory.h
 * 
 * Trajectory functions
 * 
 * author: Alex
 * date: 28.01.2020
 **/

#include "ros/ros.h"

#include <math.h>

#define LANEWIDTH 0
#define STEERINGRADIUS 2000
#define MAXSTEERINGANGLE 26

typedef struct
{
	float a; // ^0
	float b; // ^1
	float c; // ^2
	float d; // ^3
} clothoide_t;

typedef struct
{
	clothoide_t curve;
	float length;
	float lanewidth;
} trajectory_t;

trajectory_t currentTrajectory;

/* General */
void trj_init();

/* Util */
float trj_stdClothoideAt(clothoide_t clothoide, float x);
float trj_stdCircleAt(float radius, float x);

/* Overtaking */
int trj_overtake_generateMergeOutTrajectory(unsigned int laneWidth, unsigned int length, clothoide_t curve);
int trj_overtake_generateMergeBackTrajectory(unsigned int laneWidth, unsigned int length, clothoide_t curve);

float trj_overtake_getMergeOutSteeringAngleAtDistance(float distance);
float trj_overtake_getMergeBackSteeringAngleAtDistance(float distance);

/* Parking */
int trj_park_generateParkingTrajectory(unsigned int laneWidth, unsigned int parkingSpaceLength);

int trj_park_getParkInLongSteeringAngleAtDistance(float distance);
int trj_park_getParkOutLongSteeringAngleAtDistance(float distance);

int trj_park_getParkInSteeringAngleAtDistance(float distance);
int trj_park_getParkOutSteeringAngleAtDistance(float distance);

int trj_park_getParkInDirectionAtDistance(float distance);
int trj_park_getParkOutDirectionAtDistance(float distance);