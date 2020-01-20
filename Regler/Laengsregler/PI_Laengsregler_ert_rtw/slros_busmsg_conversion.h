#ifndef _SLROS_BUSMSG_CONVERSION_H_
#define _SLROS_BUSMSG_CONVERSION_H_

#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Int8.h>
#include "PI_Laengsregler_types.h"
#include "slros_msgconvert_utils.h"


void convertFromBus(std_msgs::Float32* msgPtr, SL_Bus_PI_Laengsregler_std_msgs_Float32 const* busPtr);
void convertToBus(SL_Bus_PI_Laengsregler_std_msgs_Float32* busPtr, std_msgs::Float32 const* msgPtr);

void convertFromBus(std_msgs::Int32* msgPtr, SL_Bus_PI_Laengsregler_std_msgs_Int32 const* busPtr);
void convertToBus(SL_Bus_PI_Laengsregler_std_msgs_Int32* busPtr, std_msgs::Int32 const* msgPtr);

void convertFromBus(std_msgs::Int8* msgPtr, SL_Bus_PI_Laengsregler_std_msgs_Int8 const* busPtr);
void convertToBus(SL_Bus_PI_Laengsregler_std_msgs_Int8* busPtr, std_msgs::Int8 const* msgPtr);


#endif
