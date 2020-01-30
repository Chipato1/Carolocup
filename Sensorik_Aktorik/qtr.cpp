#include "qtr.h"

QTRSensors qtr_front_left;
QTRSensors qtr_front_right;
QTRSensors qtr_back_left;
QTRSensors qtr_back_right;

void init_qtr()
{

  // configure the sensors
  qtr_front_left.setTypeAnalog();
  qtr_front_right.setTypeAnalog();
  qtr_back_left.setTypeAnalog();
  qtr_back_right.setTypeAnalog();
  qtr_front_left.setSensorPins((const uint8_t[]){A0, A1, A2},3);
  qtr_front_right.setSensorPins((const uint8_t[]){A3, A4, A5},3);
  qtr_back_left.setSensorPins((const uint8_t[]){A6, A7, A8},3);
  qtr_back_right.setSensorPins((const uint8_t[]){A9, A10, A11},3);
}

int** read_QTR()
{
  int** qtr_array = new int* [4];
  int sensorValues[3];

  for (int i=0; i<4; i++){
    qtr_array[i] = new int [3];
  }

  const int threshold = 500;
  int sensor_count = 0;
  
  //read qtr front left
  qtr_front_left.read(sensorValues);
  for (int i = 0; i < 3; i++)
  {
    if (sensorValues[i] > threshold){
      qtr_array[i][sensor_count] = 1; // 1 = white
    }
    else{
      qtr_array[i][sensor_count] = 0; // 0 = black
    }
  }
  sensor_count ++;

  //read qtr front right
  qtr_front_right.read(sensorValues);
  for (int i = 0; i < 3; i++)
  {
    if (sensorValues[i] > threshold){
      qtr_array[i][sensor_count] = 1; // 1 = white
    }
    else{
      qtr_array[i][sensor_count] = 0; // 0 = black
    }
  }
  sensor_count ++;

  //read qtr back left
  qtr_back_left.read(sensorValues);
  for (int i = 0; i < 3; i++)
  {
    if (sensorValues[i] > threshold){
      qtr_array[i][sensor_count] = 1; // 1 = white
    }
    else{
      qtr_array[i][sensor_count] = 0; // 0 = black
    }
  }
  sensor_count ++;

  //read qtr back right
  qtr_back_right.read(sensorValues);
  for (int i = 0; i < 3; i++)
  {
    if (sensorValues[i] > threshold){
      qtr_array[i][sensor_count] = 1; // 1 = white
    }
    else{
      qtr_array[i][sensor_count] = 0; // 0 = black
    }
  }
  sensor_count ++;
  
  return qtr_array;
}
