#include "aktorik.h"

void init_aktorik(){  
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

  //Alle Lichter ausschalten
  digitalWrite(blinker_links, LOW);            
  digitalWrite(blinker_rechts, LOW); 
  digitalWrite(bremslicht, LOW); 
  digitalWrite(rueckfahrlicht, LOW);
  digitalWrite(blaues_licht, LOW);
}

int aktorik(){  
  uint16_t currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    set_led_states();
    blinkstate = !blinkstate;
  }
  
  //analogvalue_1 = analogRead(tiefpass_pwm_motor_voltage_nr);//Einlesen des Pins vom Tiefpass
  //voltage = referenzvoltage * analogvalue_1; // 5V/1024 = 0.0048V pro Schritt
  //if (voltage < 0.3)//Autonom betrieb
  //{
     //digitalWrite(blaues_licht,LOW); //blaue LED auschalten
     //digitalWrite(xxxxx,On);//Multiplexer Select Pin
     //aktorik_node.spinOnce();              //Überprüfung, ob für Knoten neuer Wert vorliegt
     
  //}
  //else  //RC
  /*{
      digitalWrite(blaues_licht,HIGH); //blaue LED anschalten
      //digitalWrite(MUX_Select,HIGH);//Multiplexer Select Pin 
      motor_bewegung_RC_mode(voltage_1);
      
  }*/
  return rc_mode;
}



void servo_bewegung(float lenkwinkel_bogenmass){
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

void motor_bewegung(int16_t motor_drehzahl){
  int8_t motor_uebertragung;
  if(motor_drehzahl < 0){     //rückwärts
    motor_uebertragung = 90 +(0.234 * motor_drehzahl);
  }
  else{  //vorwärts
  motor_uebertragung = (0.236 * motor_drehzahl) + 96;
  }
  /* 
   * Übergangsbereich von 91 bis 95 wird nicht betrachtet
   */
 motor.write(motor_uebertragung);
}

void motor_bewegung_RC_mode(int16_t voltage_1){
  int8_t motor_uebertragung_RC_mode;
    if (voltage_1 < tiefpass_untere_spannung){        //rückwarts
        motor_uebertragung_RC_mode = (voltage_1 * 135.23) + 56.47;
    }
    else if (voltage_1 > tiefpass_obere_spannung){   //vorwärts
        motor_uebertragung_RC_mode = (voltage_1 * 135.23) + 58.94;
    }
    else{
        motor_uebertragung_RC_mode = 93;
    }
    motor.write(motor_uebertragung_RC_mode); 
}

void set_led_states(){
  set_output(state_light_l, blinker_links);
  set_output(state_light_r, blinker_rechts);
  set_output(state_light_b, bremslicht);
  set_output(state_light_rem, blaues_licht);
}

void set_output(int8_t state, int8_t port){
  switch(state){
    case 0: digitalWrite(port, LOW);
      break;
    case 1: digitalWrite(port, HIGH);
      break;
    case 2: 
      digitalWrite(port, blinkstate);
  }
}
