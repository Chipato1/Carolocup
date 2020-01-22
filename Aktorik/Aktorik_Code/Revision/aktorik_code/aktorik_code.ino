//Präprozessor Anweisungen

#define byte uint8_t


//Includes
#include "ros_handle.h"
#define referenzvolatage 0.0021259765
#include <ros.h>

void setup() 
{
  usb_init();
  /*
  lights_init();
  servo_init();
  motor_init();
  ;*/
}

void loop() 
{
 /* analogvalue_1 = analogRead(xxxx);//Einlesen des Pins vom Tiefpass
  voltage_1 = referenzvolatage * analogvalue_1; // 5V/1024 = 0.0048V pro Schritt
  if (voltage_1 < 0.3)//Autonom betrieb
  {
     digitalWrite(blue_light,Off); //blaue LED auschalten
     digitalWrite(xxxxx,On);//Multiplexer Select Pin
     aktorik_knoten.spinOnce();
     
  }
  else  //RC
  {
      digitalWrite(blue_light,ON); //blaue LED anschalten
      digitalWrite(xxxxx,Off);//Multiplexer Select Pin 
      motor_bewegung_RC_mode();
      
  }
  */
  aktorik_knoten.spinOnce();
}
