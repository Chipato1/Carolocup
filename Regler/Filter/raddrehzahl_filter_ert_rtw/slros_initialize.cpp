#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "raddrehzahl_filter";

// For Block raddrehzahl_filter/Subscribe1
SimulinkSubscriber<std_msgs::Float32, SL_Bus_raddrehzahl_filter_std_msgs_Float32> Sub_raddrehzahl_filter_3;

// For Block raddrehzahl_filter/Publish
SimulinkPublisher<std_msgs::Float32, SL_Bus_raddrehzahl_filter_std_msgs_Float32> Pub_raddrehzahl_filter_7;

// For Block raddrehzahl_filter/Publish1
SimulinkPublisher<std_msgs::Float32, SL_Bus_raddrehzahl_filter_std_msgs_Float32> Pub_raddrehzahl_filter_12;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

