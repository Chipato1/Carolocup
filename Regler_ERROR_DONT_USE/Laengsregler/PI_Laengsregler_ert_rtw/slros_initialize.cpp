#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "PI_Laengsregler";

// For Block PI_Laengsregler/Subscribe4
SimulinkSubscriber<std_msgs::Float32, SL_Bus_PI_Laengsregler_std_msgs_Float32> Sub_PI_Laengsregler_305;

// For Block PI_Laengsregler/Publish2
SimulinkPublisher<std_msgs::Int16, SL_Bus_PI_Laengsregler_std_msgs_Int16> Pub_PI_Laengsregler_304;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

