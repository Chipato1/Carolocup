#include "tof.h"
#include "rpm.h"
#include "aktorik.h"
#include "serial.h"

bool enable_rpm = true;

float rpm;
uint16_t* tof;

ros::NodeHandle arduino_node;

void setup() 
{  
  arduino_node.initNode();
  
  init_aktorik(&arduino_node);
  init_sensorik(&arduino_node); 
  
  init_tof(); //hat einen Rückgabewert, der angibt, ob die Initialisierung erfolgreich war
  init_rpm();
}

void loop() 
{
  //Aktorik Teil -> hier kann der Rückgabewert ausgelesen werden
  //Der Wert sagt ob der RC mode aktiviert ist 
  aktorik();
  rc_publish();
  drive_mode_publish();

  tof = read_TOF();
  tof_publish(tof[0], tof[1], tof[2], tof[3], tof[4]);
    
  if (enable_rpm){
    rpm = read_RPM();
    rpm_publish(rpm);
  }
  enable_rpm = !enable_rpm;
  
  arduino_node.spinOnce();
}
