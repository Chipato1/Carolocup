#include "sm_main.h"
//Daten in struct
//

int handleStateINIT()
{
    //get Service client QR
    //Hier kommt eigentlich nur die Bedingung QR Detected rein über service
	if (true/*Service QR detected == true*/)
	{
        //0.5 Sekunden warten 
        ros::Duration(0.5).sleep();
		return QR_CODE_DETECTED;
	}
    return INIT;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;

  //hier brauchen wir den Service Client für maxis spurerkennung
  //ros::ServiceClient client = n.serviceClient<beginner_tutorials::AddTwoInts>("QR_Detected");
  
  //Publisher .. brauchen wir bestimmt noch"
  //ros::Publisher servo_pub = n.advertise<std_msgs::UInt8>("motor", 1000);
  ros::Rate loop_rate(50);
  INIT_data.begin = ros::Time::now();
  //Initialition
  int currentState = INIT;
  //generate
  while (ros::ok())
  {
	switch (currentState)
	{
		case INIT:
			currentState = handleStateINIT();
			break;
		case QR_CODE_DETECTED:
			//...
			break;
		case DRIVE:
			//...
			break;
		default:
			ROS_INFO("You should NEVER see this");// Error
			break;
	}
    loop_rate.sleep();
  }

  return 0;
}
