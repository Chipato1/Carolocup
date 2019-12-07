#include "BMI088.h"
#include <SD.h>
#include <SPI.h>
#define CS_SD    53
/*
 * micro SD Card adapter
 * MISO 50
 * MOSI 51
 * SCK  52 
 * CS   53
 */
/* accel object */
Bmi088Accel accel(SPI,10);
/* gyro object */
Bmi088Gyro gyro(SPI,9);


File myFile;
char fileName [20];
const String header = "Time \t AccX \t AccY \t AccZ \t GyroX \t GyroY \t GyroZ";
void setup() 
{
  Serial.begin(115200);
  /* USB Serial to print data */
 while(!Serial) {delay(1);}
  if (!SD.begin(CS_SD)) {
    Serial.println("SD card initialization failed!");
  while(1);
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

 int status;
  /* USB Serial to print data */
 
  
  /* start the sensors */
  status = accel.begin();
  if (status < 0) {
    Serial.println("Accel Initialization Error");
    Serial.println(status);
    while (1) {}
  }
  status = gyro.begin();
  if (status < 0) {
    Serial.println("Gyro Initialization Error");
    Serial.println(status);
    while (1) {}
  }
}

void loop() 
{
   /* read the accel */
  accel.readSensor();
  /* read the gyro */
  gyro.readSensor();
  /* print the data */


  if(myFile){
 
  myFile.print(millis() /1000.0 ,3);
  myFile.print("\t");
  myFile.print(accel.getAccelX_mss());
  myFile.print("\t");
  myFile.print(accel.getAccelY_mss());
  myFile.print("\t");
  myFile.print(accel.getAccelZ_mss());
  myFile.print("\t");
  myFile.print(gyro.getGyroX_rads());
  myFile.print("\t");
  myFile.print(gyro.getGyroY_rads());
  myFile.print("\t");
  myFile.print(gyro.getGyroZ_rads());
  myFile.print("\n");
  
  myFile.flush();

}
  Serial.print(millis() /1000.0 ,3);
  Serial.print("\t");
  Serial.print(accel.getAccelX_mss());
  Serial.print("\t");
  Serial.print(accel.getAccelY_mss());
  Serial.print("\t");
  Serial.print(accel.getAccelZ_mss());
  Serial.print("\t");
  Serial.print(gyro.getGyroX_rads());
  Serial.print("\t");
  Serial.print(gyro.getGyroY_rads());
  Serial.print("\t");
  Serial.print(gyro.getGyroZ_rads());
  Serial.print("\n");
  delay(10);
  
}
