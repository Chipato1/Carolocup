/**
 * sm_main.h
 * 
 * Main State machine
 * 
 * author:	Alex
 * date:		28.01.2020
 **/

#include "ros/ros.h"
#include "std_msgs/UInt8.h"

#include "sm_estimation.h"
#include "trajectory.h"

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