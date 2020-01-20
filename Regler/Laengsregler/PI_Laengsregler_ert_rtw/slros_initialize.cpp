#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "PI_Laengsregler";

// For Block PI_Laengsregler/Subscribe
SimulinkSubscriber<std_msgs::Float32, SL_Bus_PI_Laengsregler_std_msgs_Float32> Sub_PI_Laengsregler_80;

// For Block PI_Laengsregler/Subscribe1
SimulinkSubscriber<std_msgs::Int32, SL_Bus_PI_Laengsregler_std_msgs_Int32> Sub_PI_Laengsregler_128;

// For Block PI_Laengsregler/Publish
SimulinkPublisher<std_msgs::Int8, SL_Bus_PI_Laengsregler_std_msgs_Int8> Pub_PI_Laengsregler_79;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

