#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "Zustandsregler";

// For Block Zustandsregler/Subscribe
SimulinkSubscriber<std_msgs::Float64, SL_Bus_Zustandsregler_std_msgs_Float64> Sub_Zustandsregler_126;

// For Block Zustandsregler/Subscribe1
SimulinkSubscriber<std_msgs::Float64, SL_Bus_Zustandsregler_std_msgs_Float64> Sub_Zustandsregler_170;

// For Block Zustandsregler/Subscribe2
SimulinkSubscriber<std_msgs::Float64, SL_Bus_Zustandsregler_std_msgs_Float64> Sub_Zustandsregler_172;

// For Block Zustandsregler/Subscribe3
SimulinkSubscriber<std_msgs::Float64, SL_Bus_Zustandsregler_std_msgs_Float64> Sub_Zustandsregler_174;

// For Block Zustandsregler/Publish
SimulinkPublisher<std_msgs::Float32, SL_Bus_Zustandsregler_std_msgs_Float32> Pub_Zustandsregler_158;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

