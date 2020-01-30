#include "tof.h"

VL53L0X_RangingMeasurementData_t measure_front;
VL53L0X_RangingMeasurementData_t measure_left;
VL53L0X_RangingMeasurementData_t measure_right;
VL53L0X_RangingMeasurementData_t measure_cross;

static uint16_t tof_array[5];

void init_tof()
{
  pinMode(ToF_front_SHT,OUTPUT);
  pinMode(ToF_left_SHT,OUTPUT);
  pinMode(ToF_right_SHT,OUTPUT);
  pinMode(ToF_cross_SHT,OUTPUT);
  pinMode(ToF_back_SHT,OUTPUT);
  
  //reset all
  digitalWrite(ToF_front_SHT,LOW);
  digitalWrite(ToF_left_SHT,LOW);
  digitalWrite(ToF_right_SHT,LOW);
  digitalWrite(ToF_cross_SHT,LOW);
  digitalWrite(ToF_back_SHT,LOW);

  //unreset all
  digitalWrite(ToF_front_SHT,HIGH);
  digitalWrite(ToF_left_SHT,HIGH);
  digitalWrite(ToF_right_SHT,HIGH);
  digitalWrite(ToF_cross_SHT,HIGH);
  digitalWrite(ToF_back_SHT,HIGH);

  //reset all
  digitalWrite(ToF_front_SHT,LOW);
  digitalWrite(ToF_left_SHT,LOW);
  digitalWrite(ToF_right_SHT,LOW);
  digitalWrite(ToF_cross_SHT,LOW);
  digitalWrite(ToF_back_SHT,LOW);
  
  //init ToF_front
  digitalWrite(ToF_front_SHT,HIGH);
  if (!ToF_front.begin(ToF_front_ADDRESS)) {
    //Serial.println(F("Failed to boot ToF_front"));
    while(1);
  }
/*
  //init ToF_left
  digitalWrite(ToF_left_SHT,HIGH);
  if (!ToF_left.begin(ToF_left_ADDRESS)) {
    Serial.println(F("Failed to boot ToF_left"));
    while(1);
  }

  //init ToF_right
  digitalWrite(ToF_right_SHT,HIGH);
  if (!ToF_right.begin(ToF_right_ADDRESS)) {
    Serial.println(F("Failed to boot ToF_right"));
    while(1);
  }

  //init ToF_cross
  digitalWrite(ToF_cross_SHT,HIGH);
  if (!ToF_cross.begin(ToF_cross_ADDRESS)) {
    Serial.println(F("Failed to boot ToF_cross"));
    while(1);
  }

  
  //init ToF_back
  digitalWrite(ToF_back_SHT,HIGH);
  if (!ToF_back.begin()) {
    Serial.println(F("Failed to boot ToF_back"));
    while(1);
  }
  */
}

uint16_t* read_TOF()
{  
  uint16_t distance_ToF_front = threshold_front;
  uint16_t distance_ToF_left = threshold_left;
  uint16_t distance_ToF_right = threshold_right;
  uint16_t distance_ToF_cross = threshold_cross;
  uint16_t distance_ToF_back = threshold_back;

  ToF_front.rangingTest(&measure_front, false); // pass in 'true' to get debug data printout!
  /*
  ToF_left.rangingTest(&measure_left, false); // pass in 'true' to get debug data printout!
  ToF_right.rangingTest(&measure_right, false); // pass in 'true' to get debug data printout!
  ToF_cross.rangingTest(&measure_cross, false); // pass in 'true' to get debug data printout!
  */

  //read ToF_front
  if (measure_front.RangeStatus != 4) {  // phase failures have incorrect data
    distance_ToF_front = measure_front.RangeMilliMeter;
    if(distance_ToF_front > threshold_front){
      distance_ToF_front = threshold_front;
    }
  } else {
    distance_ToF_front = threshold_front;
  }
  /*
  //read ToF_left
  if (measure_left.RangeStatus != 4) {  // phase failures have incorrect data
    distance_ToF_left = measure_left.RangeMilliMeter;
    if(distance_ToF_left > threshold_left){
      distance_ToF_left = threshold_left;
    }
  } else {
    distance_ToF_left = threshold_left;
  }

  //read ToF_right
  if (measure_right.RangeStatus != 4) {  // phase failures have incorrect data
    distance_ToF_right = measure_right.RangeMilliMeter;
    if(distance_ToF_right > threshold_right){
      distance_ToF_right = threshold_right;
    }
  } else {
    distance_ToF_right = threshold_right;
  }

  //read ToF_cross
  if (measure_cross.RangeStatus != 4) {  // phase failures have incorrect data
    distance_ToF_cross = measure_cross.RangeMilliMeter;
    if(distance_ToF_cross > threshold_cross){
      distance_ToF_cross = threshold_cross;
    }
  } else {
    distance_ToF_cross = threshold_cross;
  }
  
  //read ToF_back
  if ((ToF_back.readRangeStatus() < VL6180X_ERROR_SYSERR_1) || (ToF_back.readRangeStatus() > VL6180X_ERROR_SYSERR_5)){ //no system error
    distance_ToF_back = ToF_back.readRange();
    if(distance_ToF_back > threshold_back){
      distance_ToF_back = threshold_back;
    }
  }
  */
  tof_array[0] = distance_ToF_front;
  tof_array[1] = distance_ToF_left;
  tof_array[2] = distance_ToF_right;
  tof_array[3] = distance_ToF_cross;
  tof_array[4] = distance_ToF_back;

  return tof_array;
}
