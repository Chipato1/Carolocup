#ifndef serial_h
#define serial_h
#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int8.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Int16.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>

static ros::NodeHandle node;

void init_ros();

void servo_cb(const std_msgs::Float32& cmd_msg);
void motor_cb(const std_msgs::Int16& cmd_msg);
void lichtLinks_cb(const std_msgs::UInt8& light_state);
void lichtRechts_cb(const std_msgs::UInt8& light_state);
void lichtBremse_cb(const std_msgs::UInt8& light_state);
void lichtRemote_cb(const std_msgs::UInt8& light_state);

void rpm_publish(float rpm);
void tof_publish(uint16_t front, uint16_t left, uint16_t right, uint16_t cross, uint16_t back);
void rc_mode_publish(boolean RCmode);
void error_publish(boolean error);

#endif
