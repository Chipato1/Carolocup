#include "rpm.h"
#include <Arduino.h>

#define RPM_inputPin    14
#define ticks_per_cycle 4


float rpm_T1, rpm_T2, rpm_count, rpm_value;

void init_rpm(){
  pinMode(RPM_inputPin, INPUT_PULLUP);
  rpm_T1 = 0;
  rpm_T2 = 0;
  rpm_count = 0;

  attachInterrupt(0, RPM_Ticks, FALLING);
}

float read_RPM()
{
  if (rpm_T2 > rpm_T1){
    rpm_value = 60000 * rpm_count / (rpm_T2 - rpm_T1);
    rpm_T1 = rpm_T2;
    rpm_count = 0;    
  }
  else{
    rpm_value = 0;
  }
  return (rpm_value / ticks_per_cycle);
}

void RPM_Ticks(){
  rpm_count++;
  rpm_T2 = millis();
}
