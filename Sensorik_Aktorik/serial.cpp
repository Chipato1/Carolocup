#include "serial.h"

ros::NodeHandle sensorik_node;

std_msgs::Float32 rpm_msg;
std_msgs::UInt16 tof_front_msg, tof_left_msg, tof_right_msg, tof_cross_msg, tof_back_msg;
std_msgs::Int8 error_msg;

ros::Publisher rpm_pub("raddrehzahl", &rpm_msg);

ros::Publisher tof_front_pub("abstandVorne", &tof_front_msg);
ros::Publisher tof_left_pub("abstandLinks", &tof_left_msg);
ros::Publisher tof_right_pub("abstandRechts", &tof_right_msg);
ros::Publisher tof_cross_pub("abstandKreuzung", &tof_cross_msg);
ros::Publisher tof_back_pub("abstandHinten", &tof_back_msg);

ros::Publisher error_pub("error", &error_msg);


void init_ros(){
  sensorik_node.initNode();
  sensorik_node.advertise(rpm_pub);
  sensorik_node.advertise(tof_front_pub);
  sensorik_node.advertise(tof_left_pub);
  sensorik_node.advertise(tof_right_pub);
  sensorik_node.advertise(tof_cross_pub);
  sensorik_node.advertise(tof_back_pub);
  sensorik_node.advertise(error_pub);
}

/*void rpm_publish(float rpm){  
  rpm_msg.data = rpm;
  rpm_pub.publish(&rpm_msg);
}
*/

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

/*

void error_publish(int err){  
  error_msg.data = err;
  error_pub.publish(&error_msg);
}*/

void spin(){
  sensorik_node.spinOnce();
  delay(20);
}
