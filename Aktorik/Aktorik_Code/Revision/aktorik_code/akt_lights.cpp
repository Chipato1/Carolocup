#include "akt_lights.h"

void lights_init()
{
  pinMode(frontlicht, OUTPUT);              //Setzen der Lichter als Ausgang
  pinMode(blinker_links, OUTPUT);         
  pinMode(blinker_rechts, OUTPUT);        
  pinMode(bremslicht, OUTPUT);              
  pinMode(rueckfahrlicht, OUTPUT);          
  pinMode(blaues_licht, OUTPUT);

  //Sind Scheinwerfer immer an?
  digitalWrite(blinker_links,LOW);            //Alle Lichter ausschalten
  digitalWrite(blinker_rechts,LOW); 
  digitalWrite(bremslicht,LOW); 
  digitalWrite(rueckfahrlicht,LOW);
  digitalWrite(blaues_licht, LOW);
}

void licht_leuchti(byte led_signal)
{
  switch (led_signal)
  {
    case 0x00: digitalWrite(bremslicht,HIGH);
      break;
    
    case 0x01: digitalWrite(bremslicht,LOW);
      break;
      
    case 0x02: digitalWrite(blinker_rechts,HIGH);
      break;
      
    case 0x03: digitalWrite(blinker_rechts,LOW);
      break;
                 
    case 0x04: digitalWrite(blinker_links,HIGH);
       break;
              
    case 0x05: digitalWrite(blinker_links,LOW);
       break; 
    
    case 0x06: digitalWrite(rueckfahrlicht,HIGH);
      break;
    
    case 0x07: digitalWrite(rueckfahrlicht,LOW);
      break;
            
    default: //nix mache
       break;
  }
}
