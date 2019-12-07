

#include "BMI088.h"

/* accel object */
Bmi088Accel accel(SPI,10);
/* gyro object */
Bmi088Gyro gyro(SPI,9);

void setup() 
{
  int status;
  /* USB Serial to print data */
  Serial.begin(115200);
  while(!Serial) {}
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
}
