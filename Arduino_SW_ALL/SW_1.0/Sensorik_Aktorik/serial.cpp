#include "serial.h"

std_msgs::Float32 rpm_msg;
std_msgs::UInt16 tof_front_msg, tof_left_msg, tof_right_msg, tof_cross_msg, tof_back_msg;

ros::Publisher rpm_pub("sns_wheelRpm", &rpm_msg);

ros::Publisher tof_front_pub("sns_distanceFront", &tof_front_msg);
ros::Publisher tof_left_pub("sns_distanceLeft", &tof_left_msg);
ros::Publisher tof_right_pub("sns_distanceRight", &tof_right_msg);
ros::Publisher tof_cross_pub("sns_distanceCross", &tof_cross_msg);
ros::Publisher tof_back_pub("sns_distanceBack", &tof_back_msg);

void init_sensorik(ros::NodeHandle *arduino_node){
  arduino_node->advertise(rpm_pub);
  arduino_node->advertise(tof_front_pub);
  arduino_node->advertise(tof_left_pub);
  arduino_node->advertise(tof_right_pub);
  arduino_node->advertise(tof_cross_pub);
  arduino_node->advertise(tof_back_pub);
  arduino_node->advertise(error_pub);
}

void rpm_publish(float rpm){  
  rpm_msg.data = rpm;
  rpm_pub.publish(&rpm_msg);
}

void tof_publish(uint16_t front, uint16_t left, uint16_t right, uint16_t cross, uint16_t back){  
  tof_front_msg.data = front;
  tof_front_pub.publish(&tof_front_msg);
  
  tof_left_msg.data = left;
  tof_left_pub.publish(&tof_left_msg);
  
  tof_right_msg.data = right;
  tof_right_pub.publish(&tof_right_msg);
  
  tof_cross_msg.data = cross;
  tof_cross_pub.publish(&tof_cross_msg);
  
  tof_back_msg.data = back;
  tof_back_pub.publish(&tof_back_msg);
}
