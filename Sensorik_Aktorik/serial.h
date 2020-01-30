#ifndef serial_h
#define serial_h
#include <ros.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/Bool.h>

void init_ros();
void rpm_publish(float rpm);
void imu_publish(float accelX, float accelY, float gyroZ);
void tof_publish(int front, int left, int right, int cross, int back);
void qtr_publish(int* frontLeft, int* frontRight, int* backLeft, int* backRight);
void error_publish(int error);

#endif
