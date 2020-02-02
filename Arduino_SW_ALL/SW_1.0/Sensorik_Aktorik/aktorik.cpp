#include "aktorik.h"

Servo servo;
Servo motor;  

//ros::NodeHandle aktorik_node;

ros::Subscriber<std_msgs::Float32> sub_servo("ctl_servoAngle", servo_cb);
ros::Subscriber<std_msgs::Int16> sub_motor("ctl_motorRpm", motor_cb);      
ros::Subscriber<std_msgs::UInt8> sub_light_l("trj_flashLeft", lichtLinks_cb);
ros::Subscriber<std_msgs::UInt8> sub_light_r("trj_flashRight", lichtRechts_cb);
ros::Subscriber<std_msgs::UInt8> sub_light_b("trj_breakLight", lichtBremse_cb);
ros::Subscriber<std_msgs::UInt8> sub_light_rem("trj_remoteLight", lichtRemote_cb);

short rc_mode = 0;
int16_t analogvalue_1; //eingelesener Pin - Wert am Tiefpass
  
float wert_servo;
float lenkwinkel_servosize;
float lenkwinkel_grad;

//int8_t motor_uebertragung;
//int8_t motor_uebertragung_RC_mode;

short state_light_r = 0;
short state_light_l = 0;
short state_light_b = 0;
short state_light_rem = 0;

uint16_t previousMillis = 0;
boolean blinkstate = true;

void init_aktorik(ros::NodeHandle *aktorik_node){
  //aktorik_node.initNode();  //Initialisierung des ROS - Knoten
  
  aktorik_node->subscribe(sub_servo);  //Zuweisung Servo Subscriber zum Aktorik - Knoten
  aktorik_node->subscribe(sub_motor);  //Zuweisung Motor Subscriber zum Aktorik - Knoten
  aktorik_node->subscribe(sub_light_l);
  aktorik_node->subscribe(sub_light_r);
  aktorik_node->subscribe(sub_light_b);
  aktorik_node->subscribe(sub_light_rem);
  
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
  return rc_mode;
}

void servo_cb(const std_msgs::Float32& cmd_msg){   //Callback - Funktion für Servoaufruf
  servo_bewegung(cmd_msg.data);
}

void motor_cb(const std_msgs::Int16& cmd_msg){     //Callback - Funktion für Motoraufruf
  motor_bewegung(cmd_msg.data);
}

void lichtLinks_cb(const std_msgs::UInt8& light_state){
  state_light_r = light_state.data;
}
void lichtRechts_cb(const std_msgs::UInt8& light_state){
  state_light_l = light_state.data;
}
void lichtBremse_cb(const std_msgs::UInt8& light_state){
  state_light_b = light_state.data;
}
void lichtRemote_cb(const std_msgs::UInt8& light_state){
  state_light_rem = light_state.data;
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

void set_output(short state, short port){
  switch(state){
    case 0: digitalWrite(port, LOW);
      break;
    case 1: digitalWrite(port, HIGH);
      break;
    case 2: 
      digitalWrite(port, blinkstate);
  }
}
