/**
 * sm_estimation.h
 * 
 * State estimation for main state machine
 * Responsible for all state transitions that require information from other nodes or ROS services
 * 
 * author: Alex
 * date: 28.01.2020
 **/

#ifndef SM_ESTIMATION_H
#define SM_ESTIMATION_H

#include "ros/ros.h"
#include "std_msgs/Float32.h"

#include <state_machine/VisionResultMsg.h>

#include "trajectory.h"

#define SE_FALSE 0
#define SE_TRUE 1

#define SE_TIMEOUT_GATE_MS 2000
#define SE_TIMEOUT_LEAVE_BOX_MS 3000
#define SE_TIMEOUT_JUNCTION_WAIT_MS 3000
#define SE_TIMEOUT_JUNCTION_OBSTACLE_WAIT_MS 5000
#define SE_TIMEOUT_JUNCTION_DRIVE_OVER_MS 3000

#define SE_SENSOR_BUFFER_LENGTH 50

/* ROS specifics */
// Subscribers
ros::Subscriber se_sub_camerashit;

ros::Subscriber se_sub_currentSpeed;
ros::Subscriber se_sub_currentDistance;

ros::Subscriber se_sub_tof_f;
ros::Subscriber se_sub_tof_fr;
ros::Subscriber se_sub_tof_r;
ros::Subscriber se_sub_tof_l;
ros::Subscriber se_sub_tof_b;

ros::Subscriber se_sub_rcMode;

// Publishers
ros::Publisher se_pub_deltaY;
ros::Publisher se_pub_targetSpeed;
ros::Publisher se_pub_enableLateralController;
ros::Publisher se_pub_steeringAngle;

/* Topic Callbacks */
void se_cb_sub_camerashit(const state_machine::VisionResultMsg msg);

void se_cb_sub_currentSpeed(const std_msgs::Float32::ConstPtr& msg);
void se_cb_sub_currentDistance(const std_msgs::Float32::ConstPtr& msg);

void se_cb_sub_tof_f(const std_msgs::Float32::ConstPtr& msg);
void se_cb_sub_tof_fr(const std_msgs::Float32::ConstPtr& msg);
void se_cb_sub_tof_r(const std_msgs::Float32::ConstPtr& msg);
void se_cb_sub_tof_l(const std_msgs::Float32::ConstPtr& msg);
void se_cb_sub_tof_b(const std_msgs::Float32::ConstPtr& msg);

/* Sensor variables */
state_machine:::VisionResultMsg visionResult;

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

/* Timer variables */
typedef ros::Time se_timervar_t;

se_timervar_t se_timer_gate;
se_timervar_t se_timer_leaveBox;
se_timervar_t se_timer_junctionWait;
se_timervar_t se_timer_junctionDriveOver;

/* State */
int se_overtakingStartDistance;
int se_parkingStartDistance;

/* Util */
float se_getAverage(float* arr, unsigned int len);
float se_getBufferAverage(se_sensorBuffer_t* buffer);
se_timervar_t se_getCurrentTime();
int se_compareTime(se_timervar_t set, se_timervar_t target);

/* General */
void se_init();

/* Arduino state */
int se_isRCModeActivated();
int se_isStartButtonPressed();

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

#endif

void se_startJunctionDriveOverTimeout();
int se_isJunctionDriveOverTimeout();
