#include "serial.h"
#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>

ros::NodeHandle sensorik_node;

std_msgs::Int16 rpm_msg;
std_msgs::Float32 imu_msg;
std_msgs::Int16 tof_msg;
std_msgs::Int16MultiArray qtr_msg;
std_msgs::Int16 error_msg;

ros::Publisher rpm_pub("rpm", &rpm_msg);
ros::Publisher imu_pub("imu", &imu_msg);
ros::Publisher tof_pub("tof", &tof_msg);
ros::Publisher qtr_pub("qtr", &qtr_msg);
ros::Publisher error_pub("error", &error_msg);


void init_ros(){
  sensorik_node.initNode();
  sensorik_node.advertise(rpm_pub);
  sensorik_node.advertise(imu_pub);
  sensorik_node.advertise(tof_pub);
  sensorik_node.advertise(qtr_pub);
  sensorik_node.advertise(error_pub);
}

void rpm_publish(int rpm_left, int rpm_right){  
  rpm_msg.data = rpm_left;
  rpm_pub.publish(&rpm_msg);
  sensorik_node.spinOnce();
  
  rpm_msg.data = rpm_right;
  rpm_pub.publish(&rpm_msg);
  sensorik_node.spinOnce();
}

void imu_publish(float accelX, float accelY, float gyroZ){  
  imu_msg.data = accelX;
  imu_pub.publish(&imu_msg);
  sensorik_node.spinOnce();
  
  imu_msg.data = accelY;
  imu_pub.publish(&imu_msg);
  sensorik_node.spinOnce();
  
  imu_msg.data = gyroZ;
  imu_pub.publish(&imu_msg);
  sensorik_node.spinOnce();
}

void tof_publish(int front, int left, int right, int cross, int back){  
  tof_msg.data = front;
  tof_pub.publish(&tof_msg);
  sensorik_node.spinOnce();
  
  tof_msg.data = left;
  tof_pub.publish(&tof_msg);
  sensorik_node.spinOnce();
  
  tof_msg.data = right;
  tof_pub.publish(&tof_msg);
  sensorik_node.spinOnce();
  
  tof_msg.data = cross;
  tof_pub.publish(&tof_msg);
  sensorik_node.spinOnce();
  
  tof_msg.data = back;
  tof_pub.publish(&tof_msg);
  sensorik_node.spinOnce();
}

void qtr_publish(int* frontLeft, int* frontRight, int* backLeft, int* backRight){  
  qtr_msg.data = frontLeft;
  qtr_pub.publish(&qtr_msg);
  sensorik_node.spinOnce();
  
  qtr_msg.data = frontRight;
  qtr_pub.publish(&qtr_msg);
  sensorik_node.spinOnce();
  
  qtr_msg.data = backLeft;
  qtr_pub.publish(&qtr_msg);
  sensorik_node.spinOnce();
  
  qtr_msg.data = backRight;
  qtr_pub.publish(&qtr_msg);
  sensorik_node.spinOnce();
}

void error_publish(int err){  
  error_msg.data = err;
  error_pub.publish(&error_msg);
  sensorik_node.spinOnce();
}
