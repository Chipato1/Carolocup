#include "slros_busmsg_conversion.h"


// Conversions between SL_Bus_PI_Laengsregler_std_msgs_Float32 and std_msgs::Float32

void convertFromBus(std_msgs::Float32* msgPtr, SL_Bus_PI_Laengsregler_std_msgs_Float32 const* busPtr)
{
  const std::string rosMessageType("std_msgs/Float32");

  msgPtr->data =  busPtr->Data;
}

void convertToBus(SL_Bus_PI_Laengsregler_std_msgs_Float32* busPtr, std_msgs::Float32 const* msgPtr)
{
  const std::string rosMessageType("std_msgs/Float32");

  busPtr->Data =  msgPtr->data;
}


// Conversions between SL_Bus_PI_Laengsregler_std_msgs_Int16 and std_msgs::Int16

void convertFromBus(std_msgs::Int16* msgPtr, SL_Bus_PI_Laengsregler_std_msgs_Int16 const* busPtr)
{
  const std::string rosMessageType("std_msgs/Int16");

  msgPtr->data =  busPtr->Data;
}

void convertToBus(SL_Bus_PI_Laengsregler_std_msgs_Int16* busPtr, std_msgs::Int16 const* msgPtr)
{
  const std::string rosMessageType("std_msgs/Int16");

  busPtr->Data =  msgPtr->data;
}

