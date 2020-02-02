#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block PI_Laengsregler/Subscribe
extern SimulinkSubscriber<std_msgs::Float32, SL_Bus_PI_Laengsregler_std_msgs_Float32> Sub_PI_Laengsregler_154;

// For Block PI_Laengsregler/Subscribe1
extern SimulinkSubscriber<std_msgs::Float32, SL_Bus_PI_Laengsregler_std_msgs_Float32> Sub_PI_Laengsregler_155;

// For Block PI_Laengsregler/Publish
extern SimulinkPublisher<std_msgs::Int32, SL_Bus_PI_Laengsregler_std_msgs_Int32> Pub_PI_Laengsregler_157;

void slros_node_init(int argc, char** argv);

#endif
