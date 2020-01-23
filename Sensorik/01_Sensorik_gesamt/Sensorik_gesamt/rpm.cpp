#include "rpm.h"
#include "Encoder.h"

int ticks_per_cycle = 9;
int* rpm_array;

Encoder left_back(2, 3);
int RPM_left, RPM_T1_left, RPM_T2_left;
int oldPosition_left;
bool cw_left;
int diff_left;

Encoder right_back(18, 19);
int RPM_right, RPM_T1_right, RPM_T2_right;
int oldPosition_right;
bool cw_right;
int diff_right;


void init_rpm(){
  Serial.println("init rpm");
  oldPosition_left = 0;
  oldPosition_right = 0;
  diff_left = 0;
  diff_right = 0;
}


int* read_RPM()
{
  long new_left_back = left_back.read() ;
  long new_right_back = right_back.read() ;
  RPM_T2_left = millis();
  RPM_T2_right = millis();

  if(new_left_back == 0){
    RPM_left = 0;
  }
  else{
    
    if(new_left_back < oldPosition_left){
      if (cw_left == 1)
      {
        diff_left = new_left_back;
      }
      cw_left = 0;
    }
    else if (new_left_back > oldPosition_left){
      if (cw_left == 0)
      {
        diff_left = new_left_back;
      }
      cw_left = 1;
    }
    RPM_left = (unsigned)(60000 * (new_left_back - diff_left ) / (RPM_T2_left));
    RPM_left = RPM_left / ticks_per_cycle;
    oldPosition_left = new_left_back;
  }

  if(new_right_back == 0){
    RPM_right = 0;
  }
  else {
    if(new_right_back < oldPosition_right){
      if (cw_right == 1)
      {
        diff_right = new_right_back;
      }
      cw_right = 0;
    }
    else if (new_right_back > oldPosition_right){
      if (cw_right == 0)
      {
        diff_right = new_right_back;
      }
      cw_right = 1;
    }
    RPM_right = (unsigned)(60000 * (new_right_back - diff_right ) / (RPM_T2_right));
    RPM_right = RPM_right / ticks_per_cycle;
    oldPosition_right = new_right_back; 
  }
  
  rpm_array[0] = RPM_left;
  rpm_array[1] = RPM_right;
  
  return rpm_array;
}
