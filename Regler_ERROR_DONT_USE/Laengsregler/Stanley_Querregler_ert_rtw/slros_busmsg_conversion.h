#ifndef _SLROS_BUSMSG_CONVERSION_H_
#define _SLROS_BUSMSG_CONVERSION_H_

#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
#include "Stanley_Querregler_types.h"
#include "slros_msgconvert_utils.h"


void convertFromBus(std_msgs::Bool* msgPtr, SL_Bus_Stanley_Querregler_std_msgs_Bool const* busPtr);
void convertToBus(SL_Bus_Stanley_Querregler_std_msgs_Bool* busPtr, std_msgs::Bool const* msgPtr);

void convertFromBus(std_msgs::Float32* msgPtr, SL_Bus_Stanley_Querregler_std_msgs_Float32 const* busPtr);
void convertToBus(SL_Bus_Stanley_Querregler_std_msgs_Float32* busPtr, std_msgs::Float32 const* msgPtr);


#endif
