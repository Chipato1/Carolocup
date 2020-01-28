#include "sm_main.h"
//Soll man das als void machen oder gibt es was schlaueres?
//ich würde den state zurückgeben
int handleStateINIT(int currentState)
{
    //Hier kommt eigentlich nur die Bedingung QR Detected rein über service
	if (true)
	{
		return QR_CODE_DETECTED;
	}
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
  
  //Initialition
  int currentState = INIT;
  
  while (ros::ok())
  {
    
	switch (currentState)
	{
		case INIT:
			currentState = handleStateINIT(currentState);
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
