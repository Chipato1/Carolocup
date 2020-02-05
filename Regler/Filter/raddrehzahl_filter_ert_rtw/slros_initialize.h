#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block raddrehzahl_filter/Subscribe1
extern SimulinkSubscriber<std_msgs::Float32, SL_Bus_raddrehzahl_filter_std_msgs_Float32> Sub_raddrehzahl_filter_3;

// For Block raddrehzahl_filter/Publish
extern SimulinkPublisher<std_msgs::Float32, SL_Bus_raddrehzahl_filter_std_msgs_Float32> Pub_raddrehzahl_filter_7;

// For Block raddrehzahl_filter/Publish1
extern SimulinkPublisher<std_msgs::Float32, SL_Bus_raddrehzahl_filter_std_msgs_Float32> Pub_raddrehzahl_filter_12;

void slros_node_init(int argc, char** argv);

#endif
