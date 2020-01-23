#include <Encoder.h>
#include <QTRSensors.h>
#include "Arduino.h"
#include "Wire.h"  
#include "SPI.h"
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Bool.h>

#include "tof.h"
#include "qtr.h"
#include "BMI088.h"
#include "rpm.h"
#include "aktorik.h"
#include "serial.h"

int* rpm;
float* imu;
int* tof;
int** qtr;
int error = 0;

void setup() {
  Serial.begin (9600);
  while (! Serial) {}

  //init_ros();
  init_rpm();
  //init_imu();
  init_tof();
  init_qtr();
  init_aktorik();
}

void loop() {
  if(!aktorik()){
    rpm = read_RPM();
     //imu = read_IMU();  
    tof = read_TOF();
    qtr = read_QTR();
  }
  else{
    //software reset
    asm volatile ("jmp 0");
  }
  
  
  
  Serial.print("\nrpm: \n");
  for (int i=0; i<2; i++){
    Serial.print(rpm[i]);
    Serial.print("\t");
  }
  /*
  Serial.print("\nimu: \n");
  for (int i=0; i<3; i++){
    Serial.print(imu[i]);
    Serial.print("\t");
  }
  */
  Serial.print("\ntof: \n");
  for (int i=0; i<5; i++){
    Serial.print(tof[i]);
    Serial.print("\t");
  }
  
  Serial.print("\nqtr: \n");
  for (int c=0; c<4; c++){
    for (int j=0; j<3; j++){
      Serial.print(qtr[j][c]);
    }
    Serial.print("\t");
  }

  //cleaning up memory
  for (int c=0; c<4; c++){
    delete[] qtr[c];
  }
  delete[] qtr;
  
  Serial.print("\n");
  /*
  rpm_publish(rpm[0], rpm[1]);
  imu_publish(imu[0], imu[1], imu[2]);
  tof_publish(tof[0], tof[1], tof[2], tof[3], tof[4]);
  qtr_publish(qtr[0], qtr[1], qtr[2], qtr[3]);
  error_publish(error);
  */
}
