#include "rpm.h"

#define ticks_per_cycle 460
float rpm_value;

float RPM_left, RPM_timer_left;
float old_left;

float RPM_right, RPM_timer_right;
float old_right;

float prev_millis = 0;
Encoder right_back(14, 15);
Encoder left_back(16, 17);

void init_rpm(){
  old_left = 0;
  old_right = 0;
}

float read_RPM()
{
  RPM_timer_left = millis();
  if(RPM_timer_left - prev_millis == 100){
    float new_left = left_back.read();
    RPM_left = (10 * (new_left - old_left));
    RPM_left = RPM_left / ticks_per_cycle;
    old_left = new_left;
  }
  
  prev_millis = RPM_timer_left;

  /*
  //left sensor
  float new_left = left_back.read();
  RPM_timer_left = millis();
  float delta_millis = RPM_timer_left - prev_millis;
  prev_millis = millis();
  
  if((new_left == 0) || (new_left == old_left)){
    RPM_left = 0;
  }
  else{
    RPM_left = (1000 * (new_left - old_left ) / (delta_millis));
    RPM_left = RPM_left / ticks_per_cycle;
    old_left = new_left;
  }
*/
    
  //right sensor
  float new_right = right_back.read();
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
  //rpm_value = (RPM_left + RPM_right) / 2.0;
  rpm_value = RPM_left;
  
  return rpm_value;
}
