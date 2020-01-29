#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "Stanley_Querregler";

// For Block Stanley_Querregler/Subscribe2
SimulinkSubscriber<std_msgs::Float32, SL_Bus_Stanley_Querregler_std_msgs_Float32> Sub_Stanley_Querregler_66;

// For Block Stanley_Querregler/Subscribe3
SimulinkSubscriber<std_msgs::Float32, SL_Bus_Stanley_Querregler_std_msgs_Float32> Sub_Stanley_Querregler_67;

// For Block Stanley_Querregler/Publish1
SimulinkPublisher<std_msgs::Float32, SL_Bus_Stanley_Querregler_std_msgs_Float32> Pub_Stanley_Querregler_65;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

