#include "qtr.h"
#include <QTRSensors.h>
#include "DHT.h"

QTRSensors qtr_front_left;
QTRSensors qtr_front_right;
QTRSensors qtr_back_left;
QTRSensors qtr_back_right;
int** reflective_value;

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
  int sensorValues[3];

  int** values = new int* [4];
  for (int i=0; i<4; i++){
    values[i] = new int [3];
  }

  /*
  for (int i=0; i<4; i++){
    delete[] values[i];
  }
  delete[] values;
  */
  const int threshold = 500;
  int sensor_count = 0;
  
  //read qtr front left
  qtr_front_left.read(sensorValues);
  for (int i = 0; i < 3; i++)
  {
    if (sensorValues[i] > threshold){
      values[i][sensor_count] = 1; // 1 = white
    }
    else{
      values[i][sensor_count] = 0; // 0 = black
    }
  }
  sensor_count ++;

  //read qtr front right
  qtr_front_right.read(sensorValues);
  for (int i = 0; i < 3; i++)
  {
    if (sensorValues[i] > threshold){
      values[i][sensor_count] = 1; // 1 = white
    }
    else{
      values[i][sensor_count] = 0; // 0 = black
    }
  }
  sensor_count ++;

  //read qtr back left
  qtr_back_left.read(sensorValues);
  for (int i = 0; i < 3; i++)
  {
    if (sensorValues[i] > threshold){
      values[i][sensor_count] = 1; // 1 = white
    }
    else{
      values[i][sensor_count] = 0; // 0 = black
    }
  }
  sensor_count ++;

  //read qtr back right
  qtr_back_right.read(sensorValues);
  for (int i = 0; i < 3; i++)
  {
    if (sensorValues[i] > threshold){
      values[i][sensor_count] = 1; // 1 = white
    }
    else{
      values[i][sensor_count] = 0; // 0 = black
    }
  }
  sensor_count ++;
  /*
  for (int c=0; c<4; c++){
    for (int j=0; j<3; j++){
      Serial.print(values[j][c]);
    }
    Serial.print("\t");
  }
  */
  return values;
}
