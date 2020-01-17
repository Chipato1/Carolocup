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


// Conversions between SL_Bus_PI_Laengsregler_std_msgs_Int32 and std_msgs::Int32

void convertFromBus(std_msgs::Int32* msgPtr, SL_Bus_PI_Laengsregler_std_msgs_Int32 const* busPtr)
{
  const std::string rosMessageType("std_msgs/Int32");

  msgPtr->data =  busPtr->Data;
}

void convertToBus(SL_Bus_PI_Laengsregler_std_msgs_Int32* busPtr, std_msgs::Int32 const* msgPtr)
{
  const std::string rosMessageType("std_msgs/Int32");

  busPtr->Data =  msgPtr->data;
}


// Conversions between SL_Bus_PI_Laengsregler_std_msgs_Int8 and std_msgs::Int8

void convertFromBus(std_msgs::Int8* msgPtr, SL_Bus_PI_Laengsregler_std_msgs_Int8 const* busPtr)
{
  const std::string rosMessageType("std_msgs/Int8");

  msgPtr->data =  busPtr->Data;
}

void convertToBus(SL_Bus_PI_Laengsregler_std_msgs_Int8* busPtr, std_msgs::Int8 const* msgPtr)
{
  const std::string rosMessageType("std_msgs/Int8");

  busPtr->Data =  msgPtr->data;
}

