#include "aktorik.h"

void init_aktorik()
{  
  motor.attach(6); //Motor an Pin zuweisen
  servo.attach(5); //Servo an Pin zuweisen

  //Setzen der Lichter als Ausgang
  pinMode(frontlicht, OUTPUT);              
  pinMode(blinker_links, OUTPUT);         
  pinMode(blinker_rechts, OUTPUT);        
  pinMode(bremslicht, OUTPUT);              
  pinMode(rueckfahrlicht, OUTPUT);          
  pinMode(blaues_licht, OUTPUT);
  
  pinMode(MUX_Select, OUTPUT);
  pinMode(tiefpass_pwm_motor_voltage, INPUT);
  pinMode(tiefpass_rcmode_voltage, INPUT);
  

  //Alle Lichter ausschalten
  digitalWrite(blinker_links, LOW);            
  digitalWrite(blinker_rechts, LOW); 
  digitalWrite(bremslicht, LOW); 
  digitalWrite(rueckfahrlicht, LOW);
  digitalWrite(blaues_licht, LOW);
}

int aktorik()
{  
  uint16_t currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    set_led_states();
    blinkstate = !blinkstate;
  }
  
  analogvalue_rcmode = analogRead(tiefpass_rcmode_voltage_nr);    //Einlesen des Pins vom Tiefpass vom channel 4
  voltage_rcmode = referenzvoltage * analogvalue_rcmode;
  
  if (voltage_rcmode > rcmode_schwellenwert)
  {
    digitalWrite(blaues_licht, HIGH);   //balue LED einschlaten
    digitalWrite(MUX_Select, HIGH);     //Multiplexer auf RCmode umschalten
    rc_mode = 1;
    motor_bewegung_RC_mode();
  }
  
  else 
  {
    digitalWrite(blaues_licht, LOW);   //balue LED ausschalten
    digitalWrite(MUX_Select, LOW);     //Multiplexer auf autonomen Betrieb umschalten
    rc_mode = 0;
    aktorik_node.spinOnce();
  }
  
  return rc_mode;  
}



void servo_bewegung(float lenkwinkel_bogenmass)
{
  lenkwinkel_grad = (lenkwinkel_bogenmass/pi)*180;
  if(lenkwinkel_grad<=0)
  {
    lenkwinkel_servosize = ((3/2)*lenkwinkel_grad) + 96;
  }
  
  else
  {
    lenkwinkel_servosize = lenkwinkel_grad + 96;
  } 
  
  servo.write(lenkwinkel_servosize); //Servo fährt in die ensprechende Stellung
}

void motor_bewegung(int16_t motor_drehzahl)
{
  int8_t motor_uebertragung;
  
  if(motor_drehzahl < 0)
  {     //rückwärts
    motor_uebertragung = 90 + (0.234 * motor_drehzahl);
  }
  else
  {  //vorwärts
  motor_uebertragung = (0.236 * motor_drehzahl) + 96;
  }
  /* 
   * Übergangsbereich von 91 bis 95 wird nicht betrachtet
   */
 motor.write(motor_uebertragung);
}

void motor_bewegung_RC_mode()
{
  int8_t motor_uebertragung_RC_mode;
  
  analogvalue_motor_rcmode = analogRead(tiefpass_pwm_motor_voltage_nr);
  voltage_motor_rcmode = referenzvoltage * analogvalue_motor_rcmode;
  
    if (voltage_motor_rcmode < tiefpass_untere_spannung)    //rückwarts
    {        
        motor_uebertragung_RC_mode = (voltage_motor_rcmode * 135.23) + 56.47;
    }
    else if (voltage_motor_rcmode > tiefpass_obere_spannung)  //vorwärts
    {   
        motor_uebertragung_RC_mode = (voltage_motor_rcmode * 135.23) + 58.94;
    }
    else
    {
        motor_uebertragung_RC_mode = 93;
    }
    
    motor.write(motor_uebertragung_RC_mode); 
}

void set_led_states()
{
  set_output(state_light_l, blinker_links);
  set_output(state_light_r, blinker_rechts);
  set_output(state_light_b, bremslicht);
  set_output(state_light_rem, blaues_licht);
}

void set_output(int8_t state, int8_t port)
{
  switch(state)
  {
    case 0: digitalWrite(port, LOW);
      break;
    case 1: digitalWrite(port, HIGH);
      break;
    case 2: 
      digitalWrite(port, blinkstate);
  }
}
