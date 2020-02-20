#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block Stanley_Querregler/Subscribe1
extern SimulinkSubscriber<std_msgs::Bool, SL_Bus_Stanley_Querregler_std_msgs_Bool> Sub_Stanley_Querregler_75;

// For Block Stanley_Querregler/Subscribe2
extern SimulinkSubscriber<std_msgs::Float32, SL_Bus_Stanley_Querregler_std_msgs_Float32> Sub_Stanley_Querregler_65;

// For Block Stanley_Querregler/Subscribe4
extern SimulinkSubscriber<std_msgs::Float32, SL_Bus_Stanley_Querregler_std_msgs_Float32> Sub_Stanley_Querregler_78;

// For Block Stanley_Querregler/Subscribe5
extern SimulinkSubscriber<std_msgs::Float32, SL_Bus_Stanley_Querregler_std_msgs_Float32> Sub_Stanley_Querregler_83;

// For Block Stanley_Querregler/Publish1
extern SimulinkPublisher<std_msgs::Float32, SL_Bus_Stanley_Querregler_std_msgs_Float32> Pub_Stanley_Querregler_72;

void slros_node_init(int argc, char** argv);

#endif
