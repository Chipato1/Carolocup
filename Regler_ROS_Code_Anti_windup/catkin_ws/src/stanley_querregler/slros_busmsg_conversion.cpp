#include "slros_busmsg_conversion.h"


// Conversions between SL_Bus_Stanley_Querregler_std_msgs_Bool and std_msgs::Bool

void convertFromBus(std_msgs::Bool* msgPtr, SL_Bus_Stanley_Querregler_std_msgs_Bool const* busPtr)
{
  const std::string rosMessageType("std_msgs/Bool");

  msgPtr->data =  busPtr->Data;
}

void convertToBus(SL_Bus_Stanley_Querregler_std_msgs_Bool* busPtr, std_msgs::Bool const* msgPtr)
{
  const std::string rosMessageType("std_msgs/Bool");

  busPtr->Data =  msgPtr->data;
}


// Conversions between SL_Bus_Stanley_Querregler_std_msgs_Float32 and std_msgs::Float32

void convertFromBus(std_msgs::Float32* msgPtr, SL_Bus_Stanley_Querregler_std_msgs_Float32 const* busPtr)
{
  const std::string rosMessageType("std_msgs/Float32");

  msgPtr->data =  busPtr->Data;
}

void convertToBus(SL_Bus_Stanley_Querregler_std_msgs_Float32* busPtr, std_msgs::Float32 const* msgPtr)
{
  const std::string rosMessageType("std_msgs/Float32");

  busPtr->Data =  msgPtr->data;
}

