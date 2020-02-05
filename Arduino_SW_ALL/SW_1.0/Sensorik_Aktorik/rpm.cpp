#include "rpm.h"
#include <Arduino.h>

#define RPM_inputPin_Left   2
#define RPM_inputPin_Right  3
#define ticks_per_cycle     4


float rpm_T1_Left, rpm_T2_Left, rpm_value_Left;
float rpm_T1_Right, rpm_T2_Right, rpm_value_Right;
int rpm_count_Left;
int rpm_count_Right;

void init_rpm(){
  pinMode(RPM_inputPin_Left, INPUT_PULLUP);
  pinMode(RPM_inputPin_Right, INPUT_PULLUP);
  
  rpm_T1_Left = 0;
  rpm_T2_Left = 0;
  rpm_count_Left = 0;
  rpm_T1_Right = 0;
  rpm_T2_Right = 0;
  rpm_count_Right = 0;

  attachInterrupt(digitalPinToInterrupt(2), RPM_Ticks_Left, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), RPM_Ticks_Right, FALLING);
}

float read_RPM()
{
  if (rpm_T2_Left > rpm_T1_Left){
    rpm_value_Left = 60000 * rpm_count_Left / (rpm_T2_Left - rpm_T1_Left);
    rpm_T1_Left = rpm_T2_Left;
    rpm_count_Left = 0;
  }
  else{
    rpm_value_Left = 0;
  }
  
  if (rpm_T2_Right > rpm_T1_Right){
    rpm_value_Right = 60000 * rpm_count_Right / (rpm_T2_Right- rpm_T1_Right);
    rpm_T1_Right = rpm_T2_Right;
    rpm_count_Right = 0;
  }
  else{
    rpm_value_Right = 0;
  } 
  
  rpm_value_Left /= ticks_per_cycle; 
  rpm_value_Right /= ticks_per_cycle;
  //return (rpm_value_Right);
  return ((rpm_value_Left + rpm_value_Right) / 2);
}

void RPM_Ticks_Left(){
  rpm_count_Left++;
  rpm_T2_Left = millis();
}

void RPM_Ticks_Right(){
  rpm_count_Right++;
  rpm_T2_Right = millis();
}
