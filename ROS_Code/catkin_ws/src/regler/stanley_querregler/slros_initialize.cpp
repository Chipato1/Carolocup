#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "Stanley_Querregler";

// For Block Stanley_Querregler/Subscribe
SimulinkSubscriber<std_msgs::Float32, SL_Bus_Stanley_Querregler_std_msgs_Float32> Sub_Stanley_Querregler_53;

// For Block Stanley_Querregler/Subscribe1
SimulinkSubscriber<std_msgs::Float32, SL_Bus_Stanley_Querregler_std_msgs_Float32> Sub_Stanley_Querregler_57;

// For Block Stanley_Querregler/Publish
SimulinkPublisher<std_msgs::Float32, SL_Bus_Stanley_Querregler_std_msgs_Float32> Pub_Stanley_Querregler_54;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

