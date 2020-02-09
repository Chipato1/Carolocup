#include "tof.h"
#include "rpm.h"
#include "aktorik.h"
#include "serial.h"

unsigned long start_loop_time = 0;


float rpm;
uint16_t* tof;

ros::NodeHandle arduino_node;

void setup() 
{  
  arduino_node.initNode();
  arduino_node.getHardware()->setBaud(57600); //experiment :D
  init_aktorik(&arduino_node);
  init_sensorik(&arduino_node); 
  arduino_node.loginfo("Program info xxx");
  //init_tof(); 
  init_rpm();
}

void loop() 
{
  aktorik();
  
  rc_publish();
  drive_mode_publish();
  
  //t_test_publish(0);
  //t_test_publish(millis());
  
  //t_test_publish(millis());
  
  //tof = read_TOF();
  //tof_publish(tof[0], tof[1], tof[2], tof[3], tof[4]);

  rpm = read_RPM();
  if (rpm != 0){rpm_publish(rpm);}  
  
  arduino_node.spinOnce();
}
