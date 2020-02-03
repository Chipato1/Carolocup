#include "tof.h"
#include "rpm.h"
#include "aktorik.h"
#include "serial.h"

float rpm;
uint16_t* tof;
boolean error = false;

void setup() 
{
  //Serial.begin (57600);
  //while (! Serial) {}

  //init_aktorik();
  //init_rpm();
  error = init_tof();
  init_ros();
}

void loop() 
{
  //aktorik();
  //if(!aktorik()){
    //rpm = read_RPM();
    tof = read_TOF();

    rc_mode_publish(false);
    //rpm_publish(rpm);
    tof_publish(tof[0], tof[1], tof[2], tof[3], tof[4]);
    //error_publish(error);
    
  //}
  /*
  else{ //RC mode
    rc_mode_publish(true);
    //software reset
    //asm volatile ("jmp 0");
  }*/  
    
  node.spinOnce();
  delay(20);
  
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
  }
  Serial.print("\n");
  */  
}
