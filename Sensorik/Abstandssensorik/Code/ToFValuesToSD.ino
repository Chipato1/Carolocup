#include "Adafruit_VL53L0X.h"
#include "Adafruit_VL6180X.h"
#include <SD.h>
#include <SPI.h>


/*
 * micro SD Card adapter
 * MISO 50
 * MOSI 51
 * SCK  52 
 * CS   53
 */

//addresses for ToF sensors
#define ToF_front_ADDRESS 0x30
#define ToF_left_ADDRESS  0x31
#define ToF_right_ADDRESS 0x32
#define ToF_back_ADDRESS  0x33

//shutdown pins for ToF sensors
#define ToF_front_SHT     26
#define ToF_left_SHT      27
#define ToF_right_SHT     28
#define ToF_back_SHT      29

#define CS_SD             53

const Adafruit_VL53L0X ToF_front  = Adafruit_VL53L0X();
const Adafruit_VL53L0X ToF_left   = Adafruit_VL53L0X();
const Adafruit_VL53L0X ToF_right  = Adafruit_VL53L0X();
const Adafruit_VL6180X ToF_back   = Adafruit_VL6180X();

VL53L0X_RangingMeasurementData_t measure_front;
VL53L0X_RangingMeasurementData_t measure_left;
VL53L0X_RangingMeasurementData_t measure_right;

int distance_tof[4];

File myFile;
char fileName [20];
const String header = "NR \t ToF_front \t ToF_left \t ToF_right \t ToF_back";

int nr = 0;
  
void setup() {
  Serial.begin (250000);
  while (! Serial) {delay(1);}
  
  pinMode(ToF_front_SHT,OUTPUT);
  pinMode(ToF_left_SHT,OUTPUT);
  pinMode(ToF_right_SHT,OUTPUT);
  pinMode(ToF_back_SHT,OUTPUT);

  init_ToF_sensors();
  
  if (!SD.begin(CS_SD)) {
    Serial.println("SD card initialization failed!");
    while (1);
  }
  Serial.println("SD card initialization done.");

  int n = 0;
  snprintf(fileName, sizeof(fileName), "data%03d.txt", n);
  while(SD.exists(fileName)){
    n++;
    snprintf(fileName, sizeof(fileName), "data%03d.txt", n);
  }
  myFile = SD.open(fileName, FILE_WRITE);
  Serial.println(fileName);
  
  if (myFile){
    myFile.println(header);
    myFile.flush();

    Serial.println(header);
  }
  else{
    Serial.println("error opening dataXXX.txt");
  }
}

void loop() {
  
  if (myFile){
    //distance_tof = //insert when values are no longer overwritten from ToF function
    timeOfFlight();
     
    //write to SD card

    myFile.print(nr);
    myFile.print("\t");
    
    myFile.print(distance_tof[0]);
    myFile.print("\t");
    myFile.print(distance_tof[1]);
    myFile.print("\t");
    myFile.print(distance_tof[2]);
    myFile.print("\t");
    myFile.print(distance_tof[3]);
    myFile.print("\n");
    myFile.flush();

    Serial.print(nr);
    Serial.print("\t");
    Serial.print(distance_tof[0]);
    Serial.print("\t");
    Serial.print(distance_tof[1]);
    Serial.print("\t");
    Serial.print(distance_tof[2]);
    Serial.print("\t");
    Serial.print(distance_tof[3]);
    Serial.print("\n");

    nr++;
  }
  else{
    Serial.println("error opening dataXXX.txt");
  }
}


void init_ToF_sensors()
{
  //reset all
  digitalWrite(ToF_front_SHT,LOW);
  digitalWrite(ToF_left_SHT,LOW);
  digitalWrite(ToF_right_SHT,LOW);
  digitalWrite(ToF_back_SHT,LOW);
  delay(10);

  //unreset all
  digitalWrite(ToF_front_SHT,HIGH);
  digitalWrite(ToF_left_SHT,HIGH);
  digitalWrite(ToF_right_SHT,HIGH);
  digitalWrite(ToF_back_SHT,HIGH);

  digitalWrite(ToF_front_SHT,LOW);
  digitalWrite(ToF_left_SHT,LOW);
  digitalWrite(ToF_right_SHT,LOW);
  digitalWrite(ToF_back_SHT,LOW);

  //init ToF_front
  digitalWrite(ToF_front_SHT,HIGH);
  if (!ToF_front.begin(ToF_front_ADDRESS)) {
    Serial.println(F("Failed to boot ToF_front"));
    while(1);
  }

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

  //init ToF_back
  digitalWrite(ToF_back_SHT,HIGH);
  if (!ToF_back.begin(ToF_back_ADDRESS)) {
    Serial.println(F("Failed to boot ToF_back"));
    while(1);
  }
}

int *timeOfFlight()
{  
  const int threshold_front = 800;
  const int threshold_left  = 800;
  const int threshold_right = 800;
  const int threshold_back  = 200;

  int distance[4];
  int distance_ToF_front;
  int distance_ToF_left;
  int distance_ToF_right;
  int distance_ToF_back;
     
  ToF_front.rangingTest(&measure_front, false); // pass in 'true' to get debug data printout!
  ToF_left.rangingTest(&measure_left, false); // pass in 'true' to get debug data printout!
  ToF_right.rangingTest(&measure_right, false); // pass in 'true' to get debug data printout!

  //read ToF_front
  if (measure_front.RangeStatus != 4) {  // phase failures have incorrect data
    distance_ToF_front = measure_front.RangeMilliMeter;
    if(distance_ToF_front > threshold_front){
      distance_ToF_front = threshold_front;
    }
  } else {
    distance_ToF_front = threshold_front;
  }

  
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

  //read ToF_back
  if (ToF_back.readRangeStatus() == VL6180X_ERROR_NONE) {  // phase failures have incorrect data
    distance_ToF_back = ToF_back.readRange();
    if(distance_ToF_back > threshold_back){
      distance_ToF_back = threshold_back;
    }
  } else {
    distance_ToF_back = threshold_back;
  }

  distance[0] = distance_ToF_front;
  distance[1] = distance_ToF_left;
  distance[2] = distance_ToF_right;
  distance[3] = distance_ToF_back;

  // remove when not needed anymore
  distance_tof[0] = distance_ToF_front;
  distance_tof[1] = distance_ToF_left;
  distance_tof[2] = distance_ToF_right;
  distance_tof[3] = distance_ToF_back;

  return distance;
}
