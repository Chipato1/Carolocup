#include "sm_main.h"

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

	//hier brauchen wir den Service Client für maxis spurerkennung
	//ros::ServiceClient client = n.serviceClient<beginner_tutorials::AddTwoInts>("QR_Detected");

	//Publisher .. brauchen wir bestimmt noch"
	//ros::Publisher servo_pub = n.advertise<std_msgs::UInt8>("motor", 1000);

	ros::Rate loop_rate(50);
	INIT_data.begin = ros::Time::now();

	sm_init();

	while (ros::ok())
	{
		sm_step();

		loop_rate.sleep();
	}

	return 0;
}

void sm_init()
{
	se_init();

	sm_switch_state(INIT);
}

void sm_step()
{
	if (se_isRCModeActivated())
	{
		sm_switch_state(RC_MODE);
	}

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
	if (se_isStartButtonPressed())
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
		// set controller setpoint
		se_startLeaveBoxTimer();
	}

	if (se_isLeaveBoxTimeout())
	{
		sm_switch_state(DRIVE_RIGHT);
	}
}

void sm_handle_DRIVE_RIGHT()
{
	// routine for passing camera data to controller

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
	// preserve setpoints for controller

	if (se_isTrackAvailable())
	{
		sm_switch_state(DRIVE_RIGHT);
	}
}

void sm_handle_JUNCTION_BRAKE()
{
	// set brake setpoint for controller

	if (se_isCarStopped())
	{
		sm_switch_state(JUNCTION_WAIT);
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
		se_startJunctionDriveOverTimeout();
	}

	// controller setpoints

	if (se_isJunctionDriveOverTimeout())
	{
		sm_switch_state(DRIVE_RIGHT);
	}
}

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

void sm_handle_RC_MODE()
{
	if (sm_isStateChanged())
	{
		// disable controller
	}

	if (!se_isRCModeActivated())
	{
		sm_switch_state(DRIVE_RIGHT);
	}
}

void sm_handle_STOPPED();
