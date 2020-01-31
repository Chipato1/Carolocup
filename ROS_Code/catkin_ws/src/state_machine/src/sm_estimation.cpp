#include "sm_estimation.h"

/* Util */
float se_getAverage(float* arr, unsigned int len)
{
	float count = 0;

	for (int a = 0; a < len, ++a)
	{
		count += arr[a];
	}
	
	float ret = count / len;

	return ret;
}

float se_getBufferAverage(se_sensorBuffer_t* buffer)
{
	return se_getAverage(buffer->buffer, SE_SENSOR_BUFFER_LENGTH);
}

long se_getCurrentTime()
{
	return ros::Time::now();
}

int se_compareTime(se_timervar_t set, se_timervar_t target)
{
	int ret = (se_getCurrentTime() - set) > target;

	return ret;
}

void se_sensorBuffer_append(se_sensorBuffer* buffer, float value)
{
	buffer->buffer = value;
	buffer->index++;

	if (buffer->index > SE_SENSOR_BUFFER_LENGTH)
	{
		buffer->index = 0;
	}
}

/* General */
void se_init()
{
	ros::NodeHandle n;

	se_sub_camerashit = n.subscribe('', 50, se_cb_sub_camerashit); // todo

	se_sub_currentSpeed = n.subscribe('', 50, se_cb_sub_currentSpeed);
	se_sub_currentDistance = n.subscribe('', 50, se_cb_sub_currentDistance);

	se_sub_tof_f = n.subscribe('', 50, se_cb_sub_tof_f);
	se_sub_tof_fr = n.subscribe('', 50, se_cb_sub_tof_fr);
	se_sub_tof_r = n.subscribe('', 50, se_cb_sub_tof_r);
	se_sub_tof_l = n.subscribe('', 50, se_cb_sub_tof_l);
	se_sub_tof_b = n.subscribe('', 50, se_cb_sub_tof_b);
}

/* Topic Callbacks */
void se_cb_sub_camerashit(const vision:::VisionResultMsg msg)
{
	visionResult = msg->data;
}

void se_cb_sub_currentSpeed(const std_msgs::Float32::ConstPtr& msg)
{
	se_currentSpeed = msg->data;
}

void se_cb_sub_currentDistance(const std_msgs::Float32::ConstPtr& msg)
{
	se_currentDistance = msg->data;
}

void se_cb_sub_tof_f(const std_msgs::Float32::ConstPtr& msg)
{
	se_sensorBuffer_append(&se_buffer_tof_f, msg->data);
}

void se_cb_sub_tof_fr(const std_msgs::Float32::ConstPtr& msg)
{
	se_sensorBuffer_append(&se_buffer_tof_fr, msg->data);
}

void se_cb_sub_tof_r(const std_msgs::Float32::ConstPtr& msg)
{
	se_sensorBuffer_append(&se_buffer_tof_r, msg->data);
}

void se_cb_sub_tof_l(const std_msgs::Float32::ConstPtr& msg)
{
	se_sensorBuffer_append(&se_buffer_tof_l, msg->data);
}

void se_cb_sub_tof_b(const std_msgs::Float32::ConstPtr& msg)
{
	se_sensorBuffer_append(&se_buffer_tof_b, msg->data);
}

/* Arduino state */
int se_isRCModeActivated()
{
	return SE_FALSE;
}

int se_isStartButtonPressed()
{
	return SE_TRUE;
}

/* Camera */
int se_isQRCodePresent()
{
	return SE_TRUE;
}

int se_isQRCodeGone()
{
	return SE_FALSE;
}

int se_isTrackAvailable()
{
	return SE_TRUE;
}

int se_isJunctionDetected()
{
	return SE_FALSE;
}

int se_isParkingAreaDetected()
{
	return SE_FALSE;
}

/* rpm */
int se_isCarStopped()
{
	int ret = se_cb_sub_currentSpeed == 0;

	return ret;
}

/* TOFs */
int se_isJunctionObstacleDetected()
{
	int ret = (se_bufferAverage(&se_buffer_tof_fr) < 200 && se_bufferAverage(&se_buffer_tof_fr) > 50);

	return ret;
}

/* Timers */
void se_startGateTimer()
{
	se_timer_gate = se_getCurrentTime();
}

int se_isGateTimeout()
{
	int ret = se_compareTime(se_timer_gate, SE_TIMEOUT_GATE);

	return ret;
}

void se_startLeaveBoxTimer()
{
	se_timer_leaveBox = se_getCurrentTime();
}

int se_isLeaveBoxTimeout()
{
	int ret = se_compareTime(se_timer_leaveBox, SE_TIMEOUT_LEAVE_BOX);

	return ret;
}

void se_startJunctionWaitTimer()
{
	se_timer_gate = se_getCurrentTime();
}

int se_isJunctionWaitTimeout()
{
	int ret = se_compareTime(se_timer_junctionWait, SE_TIMEOUT_JUNCTION_WAIT);

	return ret;
}

void se_startJunctionObstacleWaitTimer()
{
	se_timer_gate = se_getCurrentTime();
}

int se_isJunctionObstacleWaitTimeout()
{
	int ret = se_compareTime(se_timer_junctionWait, SE_TIMEOUT_JUNCTION_OBSTACLE_WAIT);

	return ret;
}

void se_startJunctionDriveOverTimeout()
{
	se_timer_gate = se_getCurrentTime();
}

int se_isJunctionDriveOverTimeout()
{
	int ret = se_compareTime(se_timer_junctionDriveOver, SE_TIMEOUT_JUNCTION_DRIVE_OVER);

	return ret;
}