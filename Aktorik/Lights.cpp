#include "Lights.h"
//#include <MyLedMatrix.h>

void lights_init()
{
  pinMode(head_lights, OUTPUT);              //Setzen der Lichter als Ausgang
  pinMode(flash_light_left, OUTPUT);         
  pinMode(flash_light_right, OUTPUT);        
  pinMode(brake_light, OUTPUT);              
  pinMode(reversing_light, OUTPUT);          
  pinMode(blue_light, OUTPUT);

  //Sind Scheinwerfer immer an?
  digitalWrite(flasher_left,LOW);            //Alle Lichter ausschalten
  digitalWrite(flasher_right,LOW); 
  digitalWrite(brake_light,LOW); 
  digitalWrite(reversing_light,LOW);
  digitalWrite(blue_light, LOW)
}

void licht_leuchti(byte led_signal)
{
  switch (led_signal)
  {
    case 0x00: digitalWrite(brake_light,ON); 
      break;
    
    case 0x01: digitalWrite(brake_light,Off); 
      break;
      
    case 0x02: digitalWrite(flasher_right,ON);  
      break;
      
    case 0x03: digitalWrite(flasher_right,Off);  
      break;
                 
    case 0x04: digitalWrite(flasher_left,ON);   
       break;
              
    case 0x05: digitalWrite(flasher_left,Off);  
       break; 
    
    case 0x06: digitalWrite(reversing_light,ON); 
      break;
    
    case 0x07: digitalWrite(reversing_light,Off); 
      break;
            
    default:  
       break;
  }

 /*
 if (millis() - previousMillis > interval)
 {
    previousMillis = millis();
    timing_flasher = !timing_flasher;
 
    digitalWrite(flasher, timing_flasher);
}
*/
