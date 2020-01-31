
//#include "tof.h"
//#include "rpm.h"
#include "aktorik.h"
//#include "serial.h"

float rpm;
uint16_t* tof;
bool error = 0;



void setup() {
  //init_rpm();
  //init_ros();
  init_aktorik();
  //init_tof()
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  aktorik();
  //tof = read_TOF();
  //tof_publish(1, 2, 3, 4, 5); 
  //tof_publish(tof[0], tof[1], tof[2], tof[3], tof[4]); 
  
  
  //spin();
}
