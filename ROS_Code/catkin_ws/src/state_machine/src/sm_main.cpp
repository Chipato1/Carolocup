#include "sm_main.h"

#include "ros/ros.h"
#include "std_msgs/UInt8.h"


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;

  ros::Publisher servo_pub = n.advertise<std_msgs::UInt8>("motor", 1000);

  ros::Rate loop_rate(10);
  ros::Rate r(5);

  while (ros::ok())
  {

    std_msgs::UInt8 number;
    int x = 70;
    number.data = x;
    loop_rate.sleep();
  }

  return 0;
}
