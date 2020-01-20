#ifndef USB_Handle_h
#define USB_Handle_h
#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle aktorik_knoten;


ros::Subscriber<std_msgs::UInt16> sub_aktorik("servo", servo_cb);
ros::Subscriber<std_msgs::UInt16> sub_aktorik("motor", motor_cb);
ros::Subscriber<std_msgs::UInt16> sub_aktorik("licht", licht_cb);


void usb_init();

void servo_cb(const std_msgs::UInt16& cmd_msg);
void motor_cb(const std_msgs::UInt16& cmd_msg);
void licht_cb(const std_msgs::UInt16& cmd_msg);













#endif
