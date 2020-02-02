#include "ros/ros.h"
#include "std_msgs/UInt8.h"

int break_light_on = 0x00;
int break_light_off = 0x01;



void activate_breakLight(ros::Publisher light_pub){
    std_msgs::UInt8 number;
    number.data = break_light_on;
    light_pub.publish(number);
    ros::spinOnce();
}

void deactivate_breakLight(ros::Publisher light_pub){
    std_msgs::UInt8 number;
    number.data = break_light_off;
    light_pub.publish(number);
    ros::spinOnce();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;

    ros::Publisher light_pub = n.advertise<std_msgs::UInt8>("licht", 100);
    //ros::Rate loop_rate(50);
    ros::Rate brake_rate(1);

  while (ros::ok())
  {
      activate_breakLight(light_pub);
      brake_rate.sleep();
      deactivate_breakLight(light_pub);
      brake_rate.sleep();
  }

  return 0;
}


