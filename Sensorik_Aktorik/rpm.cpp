#include "rpm.h"

void init_rpm(){
  old_left = 0;
  old_right = 0;
}

float read_RPM()
{
  //left sensor
  long new_left = left_encoder.read();
  RPM_timer_left = millis();
  if((new_left == 0) || (new_left == old_left)){
    RPM_left = 0;
  }
  else{
    RPM_left = (60000 * (new_left - old_left ) / (RPM_timer_left));
    RPM_left = RPM_left / ticks_per_cycle;
    old_left = new_left;
  }

  //right sensor
  long new_right = right_encoder.read();
  RPM_timer_right = millis();
  if((new_right == 0) || (new_right == old_right)){
    RPM_right = 0;
  }
  else {
    RPM_right = (60000 * (new_right - old_right ) / (RPM_timer_right));
    RPM_right = RPM_right / ticks_per_cycle;
    old_right = new_right; 
  }
  

  //Mittelwert berechnen
  rpm_value = (RPM_left + RPM_right) / 2;
  
  return rpm_value;
}
