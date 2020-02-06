/**
 * sm_main.h
 * 
 * Main State machine
 * 
 * author:	Alex
 * date:		28.01.2020
 **/

#pragma once

#ifndef SM_MAIN_H
#define SM_MAIN_H

#include "ros/ros.h"

#include "std_msgs/UInt8.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Bool.h"

#include <vision/VisionResultMsg.h>
#include <vision/SetBool.h>

//#include "sm_estimation.h"
//#include "trajectory.h"

enum states_e {
	INIT,
	READY,
	BOX_WAIT_FOR_QR_APPEAR,
	BOX_WAIT_FOR_QR_DISAPPEAR,
	BOX_WAIT_FOR_GATE_OPENING,
	LEAVE_BOX,

	DRIVE_RIGHT,
	KEEP_TRACK_RIGHT,

	JUNCTION_BRAKE,
	JUNCTION_WAIT,
	JUNCTION_WAITFOROBSTACLE,
	JUNCTION_DRIVE_OVER,

	PARK_DRIVE,
	PARK_SEARCH,
	PARK_BRAKE,
	PARK_IN_LONG,
	PARK_IN_FRONT,
	PARK_IN_BACK,
	PARK_IN_WAIT,
	PARK_OUT_BACK,
	PARK_OUT_FRONT,
	PARK_OUT_LONG,

	OVERTAKE_MOVE_OUT,
	DRIVE_LEFT,
	KEEP_TRACK_LEFT,
	OVERTAKE_MERGE_BACK,

	RC_MODE,
	STOPPED
};

struct stateInformation
{
	int currentState;
	int stateChanged;
} stateInformation_i;


/* State machine general */

void sm_init();
void sm_step();

/* States general */

void sm_state_end_cleanup();
void sm_switch_state(int newState);
bool sm_isStateChanged();

/* State specific handles */

void sm_handle_INIT();
void sm_handle_READY();
void sm_handle_BOX_WAIT_FOR_QR_APPEAR();
void sm_handle_BOX_WAIT_FOR_QR_DISAPPEAR();
void sm_handle_BOX_WAIT_FOR_GATE_OPENING();
void sm_handle_LEAVE_BOX();

void sm_handle_DRIVE_RIGHT();
void sm_handle_KEEP_TRACK_RIGHT();

void sm_handle_JUNCTION_BRAKE();
void sm_handle_JUNCTION_WAIT();
void sm_handle_JUNCTION_WAITFOROBSTACLE();
void sm_handle_JUNCTION_DRIVE_OVER();

void sm_handle_PARK_DRIVE();
void sm_handle_PARK_SEARCH();
void sm_handle_PARK_BRAKE();
void sm_handle_PARK_IN_LONG();
void sm_handle_PARK_IN_FRONT();
void sm_handle_PARK_IN_BACK();
void sm_handle_PARK_IN_WAIT();
void sm_handle_PARK_OUT_BACK();
void sm_handle_PARK_OUT_FRONT();
void sm_handle_PARK_OUT_LONG();

void sm_handle_OVERTAKE_MOVE_OUT();
void sm_handle_DRIVE_LEFT();
void sm_handle_KEEP_TRACK_LEFT();
void sm_handle_OVERTAKE_MERGE_BACK();

void sm_handle_RC_MODE();
void sm_handle_STOPPED();

struct INIT_data {
   ros::Time begin;
} INIT_data;

/*
**
**  State Estimation
**
*/

#define SE_FALSE 0
#define SE_TRUE 1

const ros::Duration SE_TIMEOUT_GATE_MS(2);
const ros::Duration SE_TIMEOUT_LEAVE_BOX_MS(3);
const ros::Duration SE_TIMEOUT_JUNCTION_WAIT_MS(3);
const ros::Duration SE_TIMEOUT_JUNCTION_OBSTACLE_WAIT_MS(5);
const ros::Duration SE_TIMEOUT_JUNCTION_DRIVE_OVER_MS(3);

#define SE_SENSOR_BUFFER_LENGTH 10

#define SE_LIGHT_MODE_OFF 0
#define SE_LIGHT_MODE_ON 1
#define SE_LIGHT_MODE_BLINK 2

#define SE_AUTO_DRIVE_MODE_OFF 0
#define SE_AUTO_DRIVE_MODE_FREEDRIVE 1
#define SE_AUTO_DRIVE_MODE_OBSTACLEAVOIDANCE 2

/* ROS specifics */
// Subscribers
ros::Subscriber se_sub_visionResult;

ros::Subscriber se_sub_currentSpeed;
ros::Subscriber se_sub_currentDistance;

ros::Subscriber se_sub_tof_f;
ros::Subscriber se_sub_tof_fr;
ros::Subscriber se_sub_tof_r;
ros::Subscriber se_sub_tof_l;
ros::Subscriber se_sub_tof_b;

ros::Subscriber se_sub_rc_mode;
ros::Subscriber se_sub_autoDriveMode;

// Publishers
ros::Publisher se_pub_deltaY;
ros::Publisher se_pub_targetSpeed;
ros::Publisher se_pub_enableLateralControl;
ros::Publisher se_pub_steeringAngle;

ros::Publisher se_pub_flashRight;
ros::Publisher se_pub_flashLeft;
ros::Publisher se_pub_brakeLight;
ros::Publisher se_pub_remoteLight;

/* Topic Callbacks */
void se_cb_sub_visionResult(const vision::VisionResultMsg::ConstPtr& msg);

void se_cb_sub_currentSpeed(const std_msgs::Float32::ConstPtr& msg);
void se_cb_sub_currentDistance(const std_msgs::Float32::ConstPtr& msg);

void se_cb_sub_tof_f(const std_msgs::Float32::ConstPtr& msg);
void se_cb_sub_tof_fr(const std_msgs::Float32::ConstPtr& msg);
void se_cb_sub_tof_r(const std_msgs::Float32::ConstPtr& msg);
void se_cb_sub_tof_l(const std_msgs::Float32::ConstPtr& msg);
void se_cb_sub_tof_b(const std_msgs::Float32::ConstPtr& msg);

void se_cb_sub_rc_mode(const std_msgs::Bool::ConstPtr& msg);
void se_cb_sub_autoDriveMode(const std_msgs::UInt8::ConstPtr& msg);

/* Publisher functions */
void se_setDeltaY(float deltaY);
void se_setTargetSpeed(float targetSpeed);
void se_setEnableLateralControl(bool enableLateralControl);
void se_setSteeringAngle(float steeringAngle);

void se_setFlashRight(int mode);
void se_setFlashLeft(int mode);
void se_setBrakeLight(int mode);
void se_setRemoteLight(int mode);

/* Sensor variables */
vision::VisionResultMsg visionResult;

float se_currentSpeed;
float se_currentDistance;

typedef struct
{
	float buffer[SE_SENSOR_BUFFER_LENGTH];
	int index;
} se_sensorBuffer_t;

se_sensorBuffer_t se_buffer_tof_f;
se_sensorBuffer_t se_buffer_tof_fr;
se_sensorBuffer_t se_buffer_tof_r;
se_sensorBuffer_t se_buffer_tof_l;
se_sensorBuffer_t se_buffer_tof_b;

void se_sensorBuffer_append(se_sensorBuffer_t* buffer, float value);

/* RC variables */
bool se_rc_mode_activated;
int se_currentAutoDriveMode;

/* Timer variables */
ros::Time se_timer_gate;
ros::Time se_timer_leaveBox;
ros::Time se_timer_junctionWait;
ros::Time se_timer_junctionDriveOver;

/* State */
int se_overtakingStartDistance;
int se_parkingStartDistance;

/* Util */
float se_getAverage(float* arr, unsigned int len);
float se_getBufferAverage(se_sensorBuffer_t* buffer);
ros::Time se_getCurrentTime();
int se_compareTime(ros::Time set, ros::Duration target);

/* General */
void se_init();

/* Arduino state */
int se_isRCModeActivated();
int se_isInOffMode();
int se_isInFreeDriveMode();
int se_isInObstacleAvoidanceMode();

/* Camera */
int se_isQRCodePresent();
int se_isQRCodeGone();
int se_isTrackAvailable();
int se_isJunctionDetected();
int se_isParkingAreaDetected();

/* rpm */
int se_isCarStopped();

/* TOFs */
int se_isJunctionObstacleDetected();

/* Timers */
void se_startGateTimer();
int se_isGateTimeout();

void se_startLeaveBoxTimer();
int se_isLeaveBoxTimeout();

void se_startJunctionWaitTimer();
int se_isJunctionWaitTimeout();

void se_startJunctionObstacleWaitTimer();
int se_isJunctionObstacleWaitTimeout();

void se_startJunctionDriveOverTimeout();
int se_isJunctionDriveOverTimeout();

/*
**
**  Trajectory
**
*/

#include <math.h>

#define LANEWIDTH 300
#define MIN_TURNRADIUS 2000
#define MAX_STEERINGANGLE 26
#define TOF_R_OFFSET 200
#define PARKING_SPACE_BUFFER 100

#define PI 3.141592654

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

float trj_park_getParkInLongSteeringAngleAtDistance(float distance);
float trj_park_getParkOutLongSteeringAngleAtDistance(float distance);

float trj_park_getParkInSteeringAngleAtDistance(float distance);
float trj_park_getParkOutSteeringAngleAtDistance(float distance);

int trj_park_getParkInDirectionAtDistance(float distance);
int trj_park_getParkOutDirectionAtDistance(float distance);

#endif
