#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block Zustandsregler/Subscribe
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_Zustandsregler_std_msgs_Float64> Sub_Zustandsregler_126;

// For Block Zustandsregler/Subscribe1
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_Zustandsregler_std_msgs_Float64> Sub_Zustandsregler_170;

// For Block Zustandsregler/Subscribe2
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_Zustandsregler_std_msgs_Float64> Sub_Zustandsregler_172;

// For Block Zustandsregler/Subscribe3
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_Zustandsregler_std_msgs_Float64> Sub_Zustandsregler_174;

// For Block Zustandsregler/Publish
extern SimulinkPublisher<std_msgs::Float32, SL_Bus_Zustandsregler_std_msgs_Float32> Pub_Zustandsregler_158;

void slros_node_init(int argc, char** argv);

#endif
