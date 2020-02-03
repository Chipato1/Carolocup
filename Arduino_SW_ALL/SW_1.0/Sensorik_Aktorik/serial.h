#ifndef serial_h
#define serial_h
#include <ros.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Int16.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>

void init_sensorik(ros::NodeHandle *arduino_node);
void rpm_publish(float rpm);
void tof_publish(uint16_t front, uint16_t left, uint16_t right, uint16_t cross, uint16_t back);
/*void error_publish(int error);*/

#endif
