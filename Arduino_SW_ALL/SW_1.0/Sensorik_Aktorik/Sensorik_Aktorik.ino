#include "tof.h"
#include "rpm.h"
#include "aktorik.h"
#include "serial.h"

unsigned long start_loop_time = 0;

bool enable_rpm = true;

float rpm;
uint16_t* tof;

ros::NodeHandle arduino_node;

void setup() 
{  
  arduino_node.initNode();
  //arduino_node.getHardware()->setBaud(115200); //experiment :D
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
  
  tof = read_TOF();

  //t_test_publish(millis());
    
  //tof_publish(tof[0], tof[1], tof[2], tof[3], tof[4]);

    
  if (enable_rpm){
    rpm = read_RPM();
    rpm_publish(rpm);
  }
  enable_rpm = !enable_rpm;
  
  arduino_node.spinOnce();
}
