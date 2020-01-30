#include "tof.h"
#include "rpm.h"
#include "aktorik.h"
#include "serial.h"


float rpm;
uint16_t* tof;
bool error = 0;

void setup() {
  //Serial.begin (57600);
  //while (! Serial) {}

  
  //init_rpm();
  init_tof();
  //init_aktorik();
  init_ros();
  
}

void loop() {
  //aktorik();
  //if(!aktorik()){
    //rpm = read_RPM();
    //tof = read_TOF();
  //}
  //else{
    //software reset
    //asm volatile ("jmp 0");
  //}
  
  /*
  Serial.print("\nrpm: \n");
  for (int i=0; i<2; i++){
    Serial.print(rpm);
    Serial.print("\t");
  }*/
  /*
  Serial.print("\ntof: \n");
  for (int i=0; i<5; i++){
    Serial.print(tof[i]);
    Serial.print("\t");
  }*/
  //Serial.print("\n");
  
  
  //rpm_publish(rpm);
  //tof_publish(tof[0], tof[1], tof[2], tof[3], tof[4]);
  //error_publish(error);

  tof_publish(1, 2, 3, 4, 5);
 
}
