#include "tof.h"
#include "rpm.h"
#include "aktorik.h"
#include "serial.h"

float rpm;
uint16_t* tof;

/*All data should be sent with ONLY this nodehandle*/
ros::NodeHandle arduino_node;

void setup() 
{  
  arduino_node.initNode();
  //Always Init ROS first
  
  init_aktorik(&arduino_node);
  init_sensorik(&arduino_node); 
  
  init_tof();
  init_rpm();
}

void loop() 
{
  //Aktorik Teil -> hier kann der Rückgabewert ausgelesen werden
  //Der Wert sagt ob der RC mode aktiviert ist 
  aktorik();
  
  tof = read_TOF();
  rpm = read_RPM();
  tof_publish(tof[0], tof[1], tof[2], tof[3], tof[4]);
  rpm_publish(rpm);
  rc_publish(); 
  //test_publish();
  
  arduino_node.spinOnce();
}
