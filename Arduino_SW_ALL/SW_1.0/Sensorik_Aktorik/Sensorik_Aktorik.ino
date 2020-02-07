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
  
  init_aktorik(&arduino_node);
  init_sensorik(&arduino_node); 
  
  init_tof(); //hat einen Rückgabewert, der angibt, ob die Initialisierung erfolgreich war
  init_rpm();
}

void loop() 
{
  t_test_publish(0);
  //t_test_publish(millis());
  //Aktorik Teil -> hier kann der Rückgabewert ausgelesen werden
  //Der Wert sagt ob der RC mode aktiviert ist 
  //aktorik();
  //t_test_publish(millis());
  //rc_publish();
  //drive_mode_publish();

  //tof = read_TOF();
  //tof_publish(tof[0], tof[1], tof[2], tof[3], tof[4]);
    
  //if (enable_rpm){
  //  rpm = read_RPM();
  //  rpm_publish(rpm);
  //}
  //enable_rpm = !enable_rpm;

  //long time_loop = (long) millis() - (long) start_loop_time;
  //test_publish((unsigned long) time_loop);
  //test_publish(millis());
  //start_loop_time = millis();
  
  arduino_node.spinOnce();
}
