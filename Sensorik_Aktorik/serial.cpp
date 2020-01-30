#include "serial.h"

ros::NodeHandle sensorik_node;

std_msgs::Float32 rpm_msg;
std_msgs::Float32 imu_accelX_msg, imu_accelY_msg, imu_gyroZ_msg;
std_msgs::Int8 tof_front_msg, tof_left_msg, tof_right_msg, tof_cross_msg, tof_back_msg;
std_msgs::Int16MultiArray qtr_frontLeft_msg, qtr_frontRight_msg, qtr_backLeft_msg, qtr_backRight_msg;
std_msgs::Int8 error_msg;

ros::Publisher rpm_pub("raddrehzahl", &rpm_msg);

ros::Publisher imu_accelX_pub("laengsbeschleunigung", &imu_accelX_msg);
ros::Publisher imu_accelY_pub("querbeschleunigung", &imu_accelY_msg);
ros::Publisher imu_gyroZ_pub("giergeschwindigkeit", &imu_gyroZ_msg);

ros::Publisher tof_front_pub("abstandVorne", &tof_front_msg);
ros::Publisher tof_left_pub("abstandLinks", &tof_left_msg);
ros::Publisher tof_right_pub("abstandRechts", &tof_right_msg);
ros::Publisher tof_cross_pub("abstandKreuzung", &tof_cross_msg);
ros::Publisher tof_back_pub("abstandHinten", &tof_back_msg);

ros::Publisher qtr_frontLeft_pub("linieVorneLinks", &qtr_frontLeft_msg);
ros::Publisher qtr_frontRight_pub("linieVorneRechts", &qtr_frontRight_msg);
ros::Publisher qtr_backLeft_pub("linieHintenLinks", &qtr_backLeft_msg);
ros::Publisher qtr_backRight_pub("linieHintenRechts", &qtr_backRight_msg);

ros::Publisher error_pub("error", &error_msg);


void init_ros(){
  sensorik_node.initNode();
  sensorik_node.advertise(rpm_pub);
  sensorik_node.advertise(imu_accelX_pub);
  sensorik_node.advertise(imu_accelY_pub);
  sensorik_node.advertise(imu_gyroZ_pub);
  sensorik_node.advertise(tof_front_pub);
  sensorik_node.advertise(tof_left_pub);
  sensorik_node.advertise(tof_right_pub);
  sensorik_node.advertise(tof_cross_pub);
  sensorik_node.advertise(tof_back_pub);
  sensorik_node.advertise(qtr_frontLeft_pub);
  sensorik_node.advertise(qtr_frontRight_pub);
  sensorik_node.advertise(qtr_backLeft_pub);
  sensorik_node.advertise(qtr_backRight_pub);
  sensorik_node.advertise(error_pub);
}

void rpm_publish(float rpm){  
  rpm_msg.data = rpm;
  rpm_pub.publish(&rpm_msg);
  sensorik_node.spinOnce();
}

void imu_publish(float accelX, float accelY, float gyroZ){  
  imu_accelX_msg.data = accelX;
  imu_accelX_pub.publish(&imu_accelX_msg);
  sensorik_node.spinOnce();
  
  imu_accelY_msg.data = accelY;
  imu_accelY_pub.publish(&imu_accelY_msg);
  sensorik_node.spinOnce();
  
  imu_gyroZ_msg.data = gyroZ;
  imu_gyroZ_pub.publish(&imu_gyroZ_msg);
  sensorik_node.spinOnce();
}

void tof_publish(int front, int left, int right, int cross, int back){  
  tof_front_msg.data = front;
  tof_front_pub.publish(&tof_front_msg);
  sensorik_node.spinOnce();
  
  tof_left_msg.data = left;
  tof_left_pub.publish(&tof_left_msg);
  sensorik_node.spinOnce();
  
  tof_right_msg.data = right;
  tof_right_pub.publish(&tof_right_msg);
  sensorik_node.spinOnce();
  
  tof_cross_msg.data = cross;
  tof_cross_pub.publish(&tof_cross_msg);
  sensorik_node.spinOnce();
  
  tof_back_msg.data = back;
  tof_back_pub.publish(&tof_back_msg);
  sensorik_node.spinOnce();
}

void qtr_publish(int* frontLeft, int* frontRight, int* backLeft, int* backRight){  
  qtr_frontLeft_msg.data = frontLeft;
  qtr_frontLeft_pub.publish(&qtr_frontLeft_msg);
  sensorik_node.spinOnce();
  
  qtr_frontRight_msg.data = frontRight;
  qtr_frontRight_pub.publish(&qtr_frontRight_msg);
  sensorik_node.spinOnce();
  
  qtr_backLeft_msg.data = backLeft;
  qtr_backLeft_pub.publish(&qtr_backLeft_msg);
  sensorik_node.spinOnce();
  
  qtr_backRight_msg.data = backRight;
  qtr_backRight_pub.publish(&qtr_backRight_msg);
  sensorik_node.spinOnce();
}

void error_publish(int err){  
  error_msg.data = err;
  error_pub.publish(&error_msg);
  sensorik_node.spinOnce();
}
