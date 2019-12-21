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
#define LOX1_ADDRESS      0x30
#define LOX2_ADDRESS      0x31
#define LOX3_ADDRESS      0x32
#define ToF_back_ADDRESS  0x33

//shutdown pins for ToF sensors
#define LOX1_SHT      26
#define LOX2_SHT      27
#define LOX3_SHT      28
#define ToF_back_SHT  29

#define CS_SD         53

const Adafruit_VL53L0X LOX1 = Adafruit_VL53L0X();
const Adafruit_VL53L0X LOX2 = Adafruit_VL53L0X();
const Adafruit_VL53L0X LOX3 = Adafruit_VL53L0X();
const Adafruit_VL6180X ToF_back = Adafruit_VL6180X();

VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;

const int trigger1=23;
const int trigger2=25;
const int echo1=22;
const int echo2=24;

int distance_tof[4];
int distance_us[2];

File myFile;
char fileName [20];
const String header = "NR \t ToF_F \t ToF_L \t ToF_R \t US_L \t US_R";

int nr = 0;
  
void setup() {
  Serial.begin (250000);
  while (! Serial) {delay(1);}
  
  pinMode(LOX1_SHT,OUTPUT);
  pinMode(LOX2_SHT,OUTPUT);
  pinMode(LOX3_SHT,OUTPUT);
  pinMode(trigger1,OUTPUT);
  pinMode(trigger2,OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(echo2,INPUT);

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
  int threshold = 800;
  
  if (myFile){
    //distance_tof = 
    timeOfFlight(threshold);
    //distance_us = 
    ultrasonic(threshold);
     
    //write to SD card

    myFile.print(nr);
    myFile.print("\t");
    
    myFile.print(distance_tof[0]);
    myFile.print("\t");
    myFile.print(distance_tof[1]);
    myFile.print("\t");
    myFile.print(distance_tof[2]);
    
    myFile.print("\t");
    myFile.print(distance_us[0]);
    myFile.print("\t");
    myFile.print(distance_us[1]);
    myFile.print("\n");

    //myFile.println(nr+"\t"+distance_tof[0]+"\t"+distance_tof[1]+"\t"+distance_tof[2]+"\t"+distance_us[0]+"\t"+distance_us[1]);
    myFile.flush();

    Serial.print(nr);
    Serial.print("\t");

//*
    Serial.print(distance_tof[0]);
    Serial.print("\t");
    Serial.print(distance_tof[1]);
    Serial.print("\t");
    Serial.print(distance_tof[2]);
    Serial.print("\t");
    Serial.print(distance_us[0]);
    Serial.print("\t");
    Serial.print(distance_us[1]);
    Serial.print("\n");
//*/
    //Serial.println(nr+"\t"+distance_tof[0]+"\t"+distance_tof[1]+"\t"+distance_tof[2]+"\t"+distance_us[0]+"\t"+distance_us[1]);
    
    
    nr++;
  }
  else{
    Serial.println("error opening dataXXX.txt");
  }
  
  //delay(100);
}


void init_ToF_sensors()
{
  //reset all
  digitalWrite(LOX1_SHT,LOW);
  digitalWrite(LOX2_SHT,LOW);
  digitalWrite(LOX3_SHT,LOW);
  //digitalWrite(ToF_back_SHT,LOW);
  delay(10);

  //unreset all
  digitalWrite(LOX1_SHT,HIGH);
  digitalWrite(LOX2_SHT,HIGH);
  digitalWrite(LOX3_SHT,HIGH);
  //digitalWrite(ToF_back_SHT,HIGH);

  //init LOX1
  digitalWrite(LOX2_SHT,LOW);
  digitalWrite(LOX3_SHT,LOW);
  //digitalWrite(ToF_back_SHT,LOW);
  if (!LOX1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }

  //init LOX2
  digitalWrite(LOX2_SHT,HIGH);
  if (!LOX2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }

  //init LOX3
  digitalWrite(LOX3_SHT,HIGH);
  if (!LOX3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
/*
  //init ToF_back
  digitalWrite(ToF_back_SHT,HIGH);
  if (!ToF_back.begin(ToF_back_ADDRESS)) {
    Serial.println(F("Failed to boot VL6180X"));
    while(1);
  }
*/
}

int *timeOfFlight(int limit)
{  
  int distance_LOX1;
  int distance_LOX2;
  int distance_LOX3;
  //int distance_ToF_back;
  int distance[4];
     
  LOX1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  LOX2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  LOX3.rangingTest(&measure3, false); // pass in 'true' to get debug data printout!

  //read LOX1
  if (measure1.RangeStatus != 4) {  // phase failures have incorrect data
    distance_LOX1 = measure1.RangeMilliMeter;
    if(distance_LOX1 > limit){
      distance_LOX1 = limit;
    }
  } else {
    distance_LOX1 = limit;
  }

  
  //read LOX2
  if (measure2.RangeStatus != 4) {  // phase failures have incorrect data
    distance_LOX2 = measure2.RangeMilliMeter;
    if(distance_LOX2 > limit){
      distance_LOX2 = limit;
    }
  } else {
    distance_LOX2 = limit;
  }

  //read LOX3
  if (measure3.RangeStatus != 4) {  // phase failures have incorrect data
    distance_LOX3 = measure3.RangeMilliMeter;
    if(distance_LOX3 > limit){
      distance_LOX3 = limit;
    }
  } else {
    distance_LOX3 = limit;
  }
/*
  //read ToF_back
  if (ToF_back.readRangeStatus() == VL6180X_ERROR_NONE) {  // phase failures have incorrect data
    distance_ToF_back = ToF_back.readRange();
    if(distance_ToF_back > limit){
      distance_ToF_back = limit;
    }
  } else {
    distance_ToF_back = limit;
  }
*/ 
  distance[0] = distance_LOX1;
  distance[1] = distance_LOX2;
  distance[2] = distance_LOX3;
  //distance[3] = distance_ToF_back;

  distance_tof[0] = distance_LOX1;
  distance_tof[1] = distance_LOX2;
  distance_tof[2] = distance_LOX3;
  //distance_tof[3] = distance_ToF_back;
/*
  Serial.print(distance[0]);
  Serial.print("\t");
  Serial.print(distance[1]);
  Serial.print("\t");
  Serial.print(distance[2]);
  Serial.print("\t");
*/
  return distance;
}

int *ultrasonic(int limit)
{  
  long duration_US1;
  long duration_US2;
  int distance_US1;
  int distance_US2;
  int distance_US[2];

  //read ultrasonic sensor 1
  digitalWrite(trigger1,HIGH);
  delay(10);
  digitalWrite(trigger1,LOW);
  duration_US1 = pulseIn(echo1,HIGH);
  distance_US1 = duration_US1 / 2 * 0.03432 * 10;
  if (distance_US1 > limit){
    distance_US1 = limit;
  }

  //read ultrasonic sensor 2
  digitalWrite(trigger2,HIGH);
  delay(10);
  digitalWrite(trigger2,LOW);
  duration_US2 = pulseIn(echo2,HIGH);
  distance_US2 = duration_US2 / 2 * 0.03432 * 10;
  if (distance_US2 > limit){
    distance_US2 = limit;
  }

  distance_US[0] = distance_US1;
  distance_US[1] = distance_US2;
  
  distance_us[0] = distance_US1;
  distance_us[1] = distance_US2;
/*
  Serial.print(distance_US[0]);
  Serial.print("\t");
  Serial.print(distance_US[1]);
  Serial.print("\t");
*/
  return distance_US;
}
