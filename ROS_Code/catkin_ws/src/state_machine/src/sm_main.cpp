#include "sm_main.h"
#include <std_msgs/Float64.h>

/*int handleStateINIT()
{
	//get Service client QR
    //Hier kommt eigentlich nur die Bedingung QR Detected rein über service
	if (true/*Service QR detected == true*//*)
	{
        //0.5 Sekunden warten 
        ros::Duration(0.5).sleep();
		return QR_CODE_DETECTED;
	}
    return INIT;
}*/

int main(int argc, char **argv)
{
	ros::init(argc, argv, "state_machine_ext");
	ros::NodeHandle n;
	
	ROS_INFO("started state-machine and trajektorie");
	//hier brauchen wir den Service Client für maxis spurerkennung

	ros::Rate loop_rate(50);
	INIT_data.begin = ros::Time::now();

	sm_init();

	while (ros::ok())
	{
		sm_step();

		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}

void sm_init()
{
	se_init();

	se_setEnableLateralControl(SE_FALSE);
	se_setTargetSpeed(0);
	se_setSteeringAngle(0);
	se_setDeltaY(0);

	se_setFlashRight(SE_LIGHT_MODE_OFF);
	se_setFlashLeft(SE_LIGHT_MODE_OFF);
	se_setBrakeLight(SE_LIGHT_MODE_OFF);
	se_setRemoteLight(SE_LIGHT_MODE_OFF);

	sm_switch_state(INIT);
}

void sm_step()
{
	if (se_isRCModeActivated())
	{
		sm_switch_state(RC_MODE);
	}
	
	std::cout << stateInformation_i.currentState << std::endl;

	switch(stateInformation_i.currentState)
	{
	case INIT:
		sm_handle_INIT();
		break;
	
	case READY:
		sm_handle_READY();
		break;
	
	case BOX_WAIT_FOR_QR_APPEAR:
		sm_handle_BOX_WAIT_FOR_QR_APPEAR();
		break;
	
	case BOX_WAIT_FOR_QR_DISAPPEAR:
		sm_handle_BOX_WAIT_FOR_QR_DISAPPEAR();
		break;
	
	case BOX_WAIT_FOR_GATE_OPENING:
		sm_handle_BOX_WAIT_FOR_GATE_OPENING();
		break;
	
	case LEAVE_BOX:
		sm_handle_LEAVE_BOX();
		break;
	

	case DRIVE_RIGHT:
		sm_handle_DRIVE_RIGHT();
		break;
	
	case KEEP_TRACK_RIGHT:
		sm_handle_KEEP_TRACK_RIGHT();
		break;
	

	case JUNCTION_BRAKE:
		sm_handle_JUNCTION_BRAKE();
		break;
	
	case JUNCTION_WAIT:
		sm_handle_JUNCTION_WAIT();
		break;
	
	case JUNCTION_WAITFOROBSTACLE:
		sm_handle_JUNCTION_WAITFOROBSTACLE();
		break;
	
	case JUNCTION_DRIVE_OVER:
		sm_handle_JUNCTION_DRIVE_OVER();
		break;
	

	case PARK_DRIVE:
		sm_handle_PARK_DRIVE();
		break;
	
	case PARK_SEARCH:
		sm_handle_PARK_SEARCH();
		break;
	
	case PARK_BRAKE:
		sm_handle_PARK_BRAKE();
		break;
	
	case PARK_IN_LONG:
		sm_handle_PARK_IN_LONG();
		break;
	
	case PARK_IN_FRONT:
		sm_handle_PARK_IN_FRONT();
		break;
	
	case PARK_IN_BACK:
		sm_handle_PARK_IN_BACK();
		break;
	
	case PARK_IN_WAIT:
		sm_handle_PARK_IN_WAIT();
		break;
	
	case PARK_OUT_BACK:
		sm_handle_PARK_OUT_BACK();
		break;
	
	case PARK_OUT_FRONT:
		sm_handle_PARK_OUT_FRONT();
		break;
	
	case PARK_OUT_LONG:
		sm_handle_PARK_OUT_LONG();
		break;
	

	case OVERTAKE_MOVE_OUT:
		sm_handle_OVERTAKE_MOVE_OUT();
		break;
	
	case DRIVE_LEFT:
		sm_handle_DRIVE_LEFT();
		break;
	
	case KEEP_TRACK_LEFT:
		sm_handle_KEEP_TRACK_LEFT();
		break;
	
	case OVERTAKE_MERGE_BACK:
		sm_handle_OVERTAKE_MERGE_BACK();
		break;
	

	case RC_MODE:
		sm_handle_RC_MODE();
		break;
	
	case STOPPED:
		sm_handle_STOPPED();
		break;
	
	}

	sm_state_end_cleanup();
}

/* States general */

void sm_state_end_cleanup()
{
	if (stateInformation_i.stateChanged > 0)
	{
		stateInformation_i.stateChanged--;
	}
}

void sm_switch_state(int newState)
{
	stateInformation_i.currentState = newState;
	stateInformation_i.stateChanged = 2;
}

bool sm_isStateChanged()
{
	return stateInformation_i.stateChanged > 0;
}

/* State specific handles */

/* Template for handler:
void sm_handle_<STATE>()
{
	if (sm_isStateChanged())
	{
		// initialize, is called once when the state has changed
	}
	// state procedure, is called with a fixed rate
	if (<transition condition>)
	{
		sm_switch_state(<New State>);
		// end procedure
	}
}
*/

void sm_handle_INIT()
{
	// todo Set Controller off, send init to arduino
	sm_switch_state(READY);
}

void sm_handle_READY()
{
	if (!se_isInOffMode())
	{
		sm_switch_state(BOX_WAIT_FOR_QR_APPEAR);
	}
}
void sm_handle_BOX_WAIT_FOR_QR_APPEAR()
{
	if (sm_isStateChanged)
	{
		// todo start qr code service
	}

	if (se_isQRCodePresent())
	{
		sm_switch_state(BOX_WAIT_FOR_QR_DISAPPEAR);
	}
}

void sm_handle_BOX_WAIT_FOR_QR_DISAPPEAR()
{
	if (se_isQRCodeGone())
	{
		sm_switch_state(BOX_WAIT_FOR_GATE_OPENING);

		// disable QR Code service
	}
}

void sm_handle_BOX_WAIT_FOR_GATE_OPENING()
{
	if (sm_isStateChanged())
	{
		se_startGateTimer();
	}

	if (se_isGateTimeout())
	{
		sm_switch_state(LEAVE_BOX);
	}
}

void sm_handle_LEAVE_BOX()
{
	if (sm_isStateChanged())
	{
		se_setDeltaY(0);
		se_setTargetSpeed(0.15);

		se_startLeaveBoxTimer();
	}

	if (se_isLeaveBoxTimeout())
	{
		sm_switch_state(DRIVE_RIGHT);
	}
}

void sm_handle_DRIVE_RIGHT()
{
	if (sm_isStateChanged())
	{
		se_setEnableLateralControl(SE_TRUE);
		se_setTargetSpeed(0.3);
	}

	se_setDeltaY(-se_currentClothoideRight[3]);

	if (!se_isTrackAvailable())
	{
		sm_switch_state(KEEP_TRACK_RIGHT);
	}

	if (se_isJunctionDetected())
	{
		sm_switch_state(JUNCTION_BRAKE);
	}

	if (se_isParkingAreaDetected())
	{
		sm_switch_state(PARK_DRIVE);
	}
}

void sm_handle_KEEP_TRACK_RIGHT()
{
	if (sm_isStateChanged())
	{
		se_setEnableLateralControl(SE_FALSE);
		se_setTargetSpeed(0.5);
	}

	if (se_isTrackAvailable())
	{
		sm_switch_state(DRIVE_RIGHT);
	}
}

void sm_handle_JUNCTION_BRAKE()
{
	if (sm_isStateChanged())
	{
		se_setTargetSpeed(0);
		se_setBrakeLight(SE_LIGHT_MODE_ON);
	}

	if (se_isCarStopped())
	{
		sm_switch_state(JUNCTION_WAIT);
		
		se_setBrakeLight(SE_LIGHT_MODE_OFF);
	}
}

void sm_handle_JUNCTION_WAIT()
{
	if (sm_isStateChanged())
	{
		se_startJunctionWaitTimer();
		// todo reset detection?
	}

	if (se_isJunctionObstacleDetected())
	{
		sm_switch_state(JUNCTION_WAITFOROBSTACLE);
	}

	if (se_isJunctionWaitTimeout())
	{
		sm_switch_state(JUNCTION_DRIVE_OVER);
	}
}

void sm_handle_JUNCTION_WAITFOROBSTACLE()
{
	if (sm_isStateChanged())
	{
		se_startJunctionObstacleWaitTimer();
	}

	if (se_isJunctionObstacleWaitTimeout())
	{
		sm_switch_state(JUNCTION_DRIVE_OVER);
	}
}

void sm_handle_JUNCTION_DRIVE_OVER()
{
	if (sm_isStateChanged())
	{
		se_setEnableLateralControl(SE_FALSE);
		se_setSteeringAngle(0);
		se_setTargetSpeed(0.5);

		se_startJunctionDriveOverTimeout();
	}

	if (se_isJunctionDriveOverTimeout())
	{
		sm_switch_state(DRIVE_RIGHT);
	}
}

void sm_handle_PARK_DRIVE()
{

}

void sm_handle_PARK_SEARCH()
{

}

void sm_handle_PARK_BRAKE()
{

}

void sm_handle_PARK_IN_LONG()
{

}

void sm_handle_PARK_IN_FRONT()
{

}

void sm_handle_PARK_IN_BACK()
{

}

void sm_handle_PARK_IN_WAIT()
{

}

void sm_handle_PARK_OUT_BACK()
{

}

void sm_handle_PARK_OUT_FRONT()
{

}

void sm_handle_PARK_OUT_LONG()
{

}


void sm_handle_OVERTAKE_MOVE_OUT()
{

}

void sm_handle_DRIVE_LEFT()
{

}

void sm_handle_KEEP_TRACK_LEFT()
{

}

void sm_handle_OVERTAKE_MERGE_BACK()
{

}


void sm_handle_RC_MODE()
{
	if (sm_isStateChanged())
	{
		se_setEnableLateralControl(SE_FALSE);
		se_setTargetSpeed(0);
		se_setSteeringAngle(0);
		se_setDeltaY(0);

		se_setFlashRight(SE_LIGHT_MODE_OFF);
		se_setFlashLeft(SE_LIGHT_MODE_OFF);
		se_setBrakeLight(SE_LIGHT_MODE_OFF);
		se_setRemoteLight(SE_LIGHT_MODE_BLINK);
	}

	if (!se_isRCModeActivated())
	{
		sm_switch_state(DRIVE_RIGHT);

		se_setRemoteLight(SE_LIGHT_MODE_OFF);
	}
}

void sm_handle_STOPPED()
{
	if (sm_isStateChanged())
	{
		se_setEnableLateralControl(SE_FALSE);
		se_setTargetSpeed(0);
		se_setSteeringAngle(0);
		se_setDeltaY(0);

		se_setFlashRight(SE_LIGHT_MODE_OFF);
		se_setFlashLeft(SE_LIGHT_MODE_OFF);
		se_setBrakeLight(SE_LIGHT_MODE_OFF);
		se_setRemoteLight(SE_LIGHT_MODE_OFF);
	}
}

/*
**
**  State Estimation
**
*/

/* Util */
float se_getAverage(float* arr, unsigned int len)
{
	float count = 0;

	for (int a = 0; a < len; ++a)
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

ros::Time se_getCurrentTime()
{
	return ros::Time::now(); // todo make ms
}

int se_compareTime(ros::Time set, ros::Duration target)
{
	int ret = ((se_getCurrentTime() - set) > target);

	return ret;
}

void se_sensorBuffer_append(se_sensorBuffer_t* buffer, float value)
{
	*(buffer->buffer) = value;
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

	// Subscribers

	se_sub_visionResult = n.subscribe("visionresult", 10, se_cb_sub_visionResult);

	se_sub_currentSpeed = n.subscribe("ctl_velocity", 50, se_cb_sub_currentSpeed);
	se_sub_currentDistance = n.subscribe("ctl_distance", 50, se_cb_sub_currentDistance);

	se_sub_tof_f = n.subscribe("sns_distanceFront", 50, se_cb_sub_tof_f);
	se_sub_tof_fr = n.subscribe("sns_distanceCross", 50, se_cb_sub_tof_fr);
	se_sub_tof_r = n.subscribe("sns_distancRight", 50, se_cb_sub_tof_r);
	se_sub_tof_l = n.subscribe("sns_distanceLeft", 50, se_cb_sub_tof_l);
	se_sub_tof_b = n.subscribe("sns_distanceBack", 50, se_cb_sub_tof_b);

	se_sub_rc_mode = n.subscribe("akt_rc", 50, se_cb_sub_rc_mode);
	se_sub_autoDriveMode = n.subscribe("akt_autoDriveMode", 50, se_cb_sub_autoDriveMode);

	// Publishers

	se_pub_deltaY = n.advertise<std_msgs::Float32>("trj_deltaY", 1000);
	se_pub_targetSpeed = n.advertise<std_msgs::Float32>("trj_targetSpeed", 1000);
	se_pub_enableLateralControl = n.advertise<std_msgs::Bool>("trj_enableLateralControl", 1000);
	se_pub_steeringAngle = n.advertise<std_msgs::Float32>("trj_steeringAngle", 1000);

	se_pub_flashRight = n.advertise<std_msgs::UInt8>("trj_flashRight", 1000);
	se_pub_flashLeft = n.advertise<std_msgs::UInt8>("trj_flashLeft", 1000);
	se_pub_brakeLight = n.advertise<std_msgs::UInt8>("trj_brakeLight", 1000);
	se_pub_remoteLight = n.advertise<std_msgs::UInt8>("trj_remoteLight", 1000);

	// State

	se_rc_mode_activated = SE_FALSE;
	se_currentAutoDriveMode = SE_AUTO_DRIVE_MODE_OFF;

	se_currentSpeed = 0;
	se_currentDistance = 0;
	
	se_currentClothoideRight[0] = 0;
	se_currentClothoideRight[1] = 0;
	se_currentClothoideRight[2] = 0;
	se_currentClothoideRight[3] = 0;

	se_currentClothoideLeft[0] = 0;
	se_currentClothoideLeft[1] = 0;
	se_currentClothoideLeft[2] = 0;
	se_currentClothoideLeft[3] = 0;

	// todo initialize buffers
}

double getMidValue(double val1, double val2)
{
	return (val1 + ((val2 - val1) / 2));
}

/* Topic Callbacks */
void se_cb_sub_visionResult(const vision::VisionResultMsg::ConstPtr& msg)
{
	std::cout << "vr - ";
	
	std_msgs::Float64 new_r_delta;
	std_msgs::Float64 new_r_phi;
	std_msgs::Float64 new_r_c0;
	std_msgs::Float64 new_r_c1;

	std_msgs::Float64 new_m_delta;
	std_msgs::Float64 new_m_phi;
	std_msgs::Float64 new_m_c0;
	std_msgs::Float64 new_m_c1;
	
	std_msgs::Float64 new_l_delta;
	std_msgs::Float64 new_l_phi;
	std_msgs::Float64 new_l_c0;
	std_msgs::Float64 new_l_c1;
	
	if (msg->foundLL && msg->solvedLL1)
	{
		//std::cout << "WAS HERE 1"<< "\n";
		if (msg->foundML && msg->solvedML1)
		{
			//std::cout << "WAS HERE 2"<< "\n";
			//new_l_c1 = getMidValue(msg->leftLane1[0], msg->middleLane1[0]);
			//new_l_c0 = getMidValue(msg->leftLane1[1], msg->middleLane1[1]);
			//new_l_phi = getMidValue(msg->leftLane1[2], msg->middleLane1[2]);
			//new_l_delta = getMidValue(msg->leftLane1[3], msg->middleLane1[3]);

			/*se_currentClothoideLeft[0] = new_l_c1;
			se_currentClothoideLeft[1] = new_l_c0;
			se_currentClothoideLeft[2] = new_l_phi;
			se_currentClothoideLeft[3] = new_l_delta;*/
		}

	}

	if (msg->foundML && msg->solvedML1)
	{
		std::cout << "M - ";
		if (msg->foundRL && msg->solvedRL1)
		{
			std::cout << "R - ";

			new_r_c1.data = msg->rightLane1[0];
			new_r_c0.data = msg->rightLane1[1];
			new_r_phi.data = msg->rightLane1[2];
			new_r_delta.data = msg->rightLane1[3];

			new_m_c1.data = msg->middleLane1[0];
			new_m_c0.data = msg->middleLane1[1];
			new_m_phi.data = msg->middleLane1[2];
			new_m_delta.data = msg->middleLane1[3];
			
			se_currentClothoideRight[0] = getMidValue(new_m_c1.data, new_r_c1.data);
			se_currentClothoideRight[1] = getMidValue(new_m_c0.data, new_r_c0.data);
			se_currentClothoideRight[2] = getMidValue(new_m_phi.data, new_r_phi.data);
			se_currentClothoideRight[3] = getMidValue(new_m_delta.data, new_r_delta.data);

			std::cout << "r: " << new_r_delta.data << " - m: " << new_m_delta.data << "\n -deltaY: " << se_currentClothoideRight[3] << "\n";

			std::cout << se_currentClothoideRight[3] << "\n";
		}
		else
		{
			new_m_c1.data = msg->middleLane1[0];
			new_m_c0.data = msg->middleLane1[1];
			new_m_phi.data = msg->middleLane1[2];
			new_m_delta.data = msg->middleLane1[3];
			
			se_currentClothoideRight[0] = new_m_c1.data;
			se_currentClothoideRight[1] = new_m_c0.data;
			se_currentClothoideRight[2] = new_m_phi.data;
			se_currentClothoideRight[3] = -new_m_delta.data + 200;

			std::cout << "m: " << new_m_delta.data << "\n -deltaY: " << se_currentClothoideRight[3] << "\n";
		}
	}
	else if (msg->foundRL && msg->solvedRL1)
	{
		std::cout << "R - ";

		new_r_c1.data = msg->rightLane1[0];
		new_r_c0.data = msg->rightLane1[1];
		new_r_phi.data = msg->rightLane1[2];
		new_r_delta.data = msg->rightLane1[3];
		
		se_currentClothoideRight[0] = new_r_c1.data;
		se_currentClothoideRight[1] = new_r_c0.data;
		se_currentClothoideRight[2] = new_r_phi.data;
		se_currentClothoideRight[3] = -new_r_delta.data - 200;

		std::cout << "r: " << new_r_delta.data << "\n -deltaY: " << se_currentClothoideRight[3] << "\n";
	}


	/*
	std::cout << new_r_c1;
	std::cout << " _ ";
	std::cout << new_r_c0;
	std::cout << " _ ";
	std::cout << new_r_phi;
	std::cout << " _ ";
	std::cout << new_r_delta;
	std::cout << " _ ";*/
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

void se_cb_sub_rc_mode(const std_msgs::Bool::ConstPtr& msg)
{
	se_rc_mode_activated = msg->data;
}

void se_cb_sub_autoDriveMode(const std_msgs::Int16::ConstPtr& msg)
{
	se_currentAutoDriveMode = msg->data;
}

/* Publisher functions */
void se_setDeltaY(float deltaY)
{
	std_msgs::Float32 msg;
	msg.data = deltaY;
	se_pub_deltaY.publish(msg);
}

void se_setTargetSpeed(float targetSpeed)
{
	std_msgs::Float32 msg;
	msg.data = targetSpeed;
	se_pub_targetSpeed.publish(msg);
}

void se_setEnableLateralControl(bool enableLateralControl)
{
	std_msgs::Bool msg;
	msg.data = enableLateralControl;
	se_pub_enableLateralControl.publish(msg);
}

void se_setSteeringAngle(float steeringAngle)
{
	std_msgs::Float32 msg;
	msg.data = steeringAngle;
	se_pub_steeringAngle.publish(msg);
}

void se_setFlashRight(int mode)
{
	std_msgs::UInt8 msg;
	msg.data = mode;
	se_pub_flashRight.publish(msg);
}

void se_setFlashLeft(int mode)
{
	std_msgs::UInt8 msg;
	msg.data = mode;
	se_pub_flashLeft.publish(msg);
}

void se_setBrakeLight(int mode)
{
	std_msgs::UInt8 msg;
	msg.data = mode;
	se_pub_brakeLight.publish(msg);
}

void se_setRemoteLight(int mode)
{
	std_msgs::UInt8 msg;
	msg.data = mode;
	se_pub_remoteLight.publish(msg);
}

/* Arduino state */
int se_isRCModeActivated()
{
	return se_rc_mode_activated;
}

int se_isInOffMode()
{
	return se_currentAutoDriveMode == SE_AUTO_DRIVE_MODE_OFF;
}

int se_isInFreeDriveMode()
{
	return se_currentAutoDriveMode == SE_AUTO_DRIVE_MODE_FREEDRIVE;
}

int se_isInObstacleAvoidanceMode()
{
	return se_currentAutoDriveMode == SE_AUTO_DRIVE_MODE_OBSTACLEAVOIDANCE;
}

/* Camera */
int se_isQRCodePresent()
{
	return SE_TRUE;
}

int se_isQRCodeGone()
{
	return SE_TRUE;
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
	int ret = (se_getBufferAverage(&se_buffer_tof_fr) < 200 && se_getBufferAverage(&se_buffer_tof_fr) > 50);

	return ret;
}

/* Timers */
void se_startGateTimer()
{
	se_timer_gate = se_getCurrentTime();
}

int se_isGateTimeout()
{
	int ret = se_compareTime(se_timer_gate, SE_TIMEOUT_GATE_MS);

	return ret;
}

void se_startLeaveBoxTimer()
{
	se_timer_leaveBox = se_getCurrentTime();
}

int se_isLeaveBoxTimeout()
{
	int ret = se_compareTime(se_timer_leaveBox, SE_TIMEOUT_LEAVE_BOX_MS);

	return ret;
}

void se_startJunctionWaitTimer()
{
	se_timer_gate = se_getCurrentTime();
}

int se_isJunctionWaitTimeout()
{
	int ret = se_compareTime(se_timer_junctionWait, SE_TIMEOUT_JUNCTION_WAIT_MS);

	return ret;
}

void se_startJunctionObstacleWaitTimer()
{
	se_timer_gate = se_getCurrentTime();
}

int se_isJunctionObstacleWaitTimeout()
{
	int ret = se_compareTime(se_timer_junctionWait, SE_TIMEOUT_JUNCTION_OBSTACLE_WAIT_MS);

	return ret;
}

void se_startJunctionDriveOverTimeout()
{
	se_timer_gate = se_getCurrentTime();
}

int se_isJunctionDriveOverTimeout()
{
	int ret = se_compareTime(se_timer_junctionDriveOver, SE_TIMEOUT_JUNCTION_DRIVE_OVER_MS);

	return ret;
}

/*
**
**  Trajectory
**
*/

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
