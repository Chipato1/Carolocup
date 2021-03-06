

#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Float32.h>


void ros_init();

void servo_cb(const std_msgs::Float32& cmd_msg);
void motor_cb(const std_msgs::UInt8& cmd_msg);
void licht_cb(const std_msgs::UInt8& cmd_msg);

static ros::NodeHandle aktorik_knoten;


static ros::Subscriber<std_msgs::Float32> sub_servo("servo", servo_cb);
static ros::Subscriber<std_msgs::UInt8> sub_motor("motor", motor_cb);
static ros::Subscriber<std_msgs::UInt8> sub_licht("licht", licht_cb);
