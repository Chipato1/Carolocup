#include "tof.h"
//#include "rpm.h"
#include "aktorik.h"
#include "serial.h"

unsigned long start_loop_time = 0;
//float rpm;
uint16_t* tof;

ros::NodeHandle arduino_node;

std_msgs::UInt16 arduino_watchdog_cnt; //Carl 13.30
ros::Publisher watchdog_pub("watchdog_value", &arduino_watchdog_cnt); //Carl 13.30

void setup() 
{  
  arduino_node.advertise(watchdog_pub);//Carl 13.30
  arduino_watchdog_cnt.data = 0;//Carl 13.30
  
  arduino_node.initNode();
  arduino_node.getHardware()->setBaud(57600); //experiment :D
  init_aktorik(&arduino_node);
  init_sensorik(&arduino_node); 
  arduino_node.loginfo("Program info xxx");
  
  init_tof(); 
  //init_rpm();
}

void loop() 
{
  t_test_publish(millis());
  aktorik();
  
  rc_publish();
  drive_mode_publish();
  
  tof = read_TOF();
  tof_publish(tof[0], tof[1], tof[2], tof[3], tof[4]);

  //rpm = read_RPM();
  //if (rpm != 0){rpm_publish(rpm);}  


  //   -> Carl 13.30
  watchdog_pub.publish(&arduino_watchdog_cnt);
  arduino_watchdog_cnt.data = arduino_watchdog_cnt.data + 1;
  
  if (arduino_watchdog_cnt.data == 101){
    arduino_watchdog_cnt.data = 0;
  }
  // Carl 13.30 <-
  
  arduino_node.spinOnce();
}
