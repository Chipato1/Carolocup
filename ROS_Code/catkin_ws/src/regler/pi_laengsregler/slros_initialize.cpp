#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "PI_Laengsregler";

// For Block PI_Laengsregler/Subscribe
SimulinkSubscriber<std_msgs::Float32, SL_Bus_PI_Laengsregler_std_msgs_Float32> Sub_PI_Laengsregler_154;

// For Block PI_Laengsregler/Subscribe1
SimulinkSubscriber<std_msgs::Float32, SL_Bus_PI_Laengsregler_std_msgs_Float32> Sub_PI_Laengsregler_155;

// For Block PI_Laengsregler/Publish
SimulinkPublisher<std_msgs::Int32, SL_Bus_PI_Laengsregler_std_msgs_Int32> Pub_PI_Laengsregler_157;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

