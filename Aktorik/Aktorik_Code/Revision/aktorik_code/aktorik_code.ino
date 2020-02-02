//Präprozessor Anweisungen

//#define byte uint8_t
//#define unsigned char byte

/*Includes
#include "akt_lights.h"
#include "akt_motor.h"

#include <Arduino.h>
#include "ros_handle.h"
#include "akt_servo.h"
#include <Servo.h>*/

#include <std_msgs/UInt16.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Float32.h>

#define referenzvolatage 0.0021259765
#include <ros.h>

void setup() 
{
  //lights_init();
  //motor_init();
  //servo_init();
  //ros_init();
  servo_servo.attach(11);
}


void loop() 
{
  
  
  
  
  while(1)
  {}
  /*byte voltage_1;
  byte analogvalue_1;
  //analogvalue_1 = analogRead(xxxx);//Einlesen des Pins vom Tiefpass
  voltage_1 = referenzvolatage * analogvalue_1; // 5V/1024 = 0.0048V pro Schritt
  if (voltage_1 < 0.3)//Autonom betrieb
  {
     //digitalWrite(blaues_licht,LOW); //blaue LED auschalten
     //digitalWrite(xxxxx,On);//Multiplexer Select Pin
     aktorik_knoten.spinOnce();
     
  }
  else  //RC
  {
      //digitalWrite(blaues_licht,HIGH); //blaue LED anschalten
      //digitalWrite(xxxxx,Off);//Multiplexer Select Pin 
      //motor_bewegung_RC_mode(voltage_1);
      
  }*/

}

void servo_cb(const std_msgs::Float32& cmd_msg)
{
}
