#include "aktorik.h"

Servo servo;
Servo motor;  

ros::NodeHandle aktorik_node;                   //Initialisierung des ROS - Knoten

ros::Subscriber<std_msgs::Float32> sub_servo("servo", servo_cb);  //Deklaration von Servo - Topic
ros::Subscriber<std_msgs::UInt8> sub_motor("motor", motor_cb);    //Deklaration von Motor - Topic
ros::Subscriber<std_msgs::UInt8> sub_licht("licht", licht_cb);    //Deklaration von Licht - Topic

int rc_mode = 0;
int analogvalue_1;                            //eingelesener Pin - Wert am Tiefpass
  
float wert_servo;
float lenkwinkel_servosize;
float lenkwinkel_grad;

byte motor_uebertragung;
byte motor_uebertragung_RC_mode;

const byte frontlicht = 53;                 //Pinbelegung der LEDs
const byte blinker_links = 51;
const byte blinker_rechts = 49;
const byte bremslicht = 47;
const byte rueckfahrlicht = 45;
const byte blaues_licht = 43;

void init_aktorik(){
  aktorik_node.initNode();  //Initialisierung des ROS - Knoten
  
  aktorik_node.subscribe(sub_servo);  //Zuweisung Servo Subscriber zum Aktorik - Knoten
  aktorik_node.subscribe(sub_motor);  //Zuweisung Motor Subscriber zum Aktorik - Knoten
  aktorik_node.subscribe(sub_licht);  //Zuweisung Licht Subscriber zum Aktorik - Knoten

  motor.attach(12); //Motor an Pin zuweisen
  servo.attach(11); //Servo an Pin zuweisen

  pinMode(frontlicht, OUTPUT);              //Setzen der Lichter als Ausgang
  pinMode(blinker_links, OUTPUT);         
  pinMode(blinker_rechts, OUTPUT);        
  pinMode(bremslicht, OUTPUT);              
  pinMode(rueckfahrlicht, OUTPUT);          
  pinMode(blaues_licht, OUTPUT);

  //Alle Lichter ausschalten
  digitalWrite(blinker_links, LOW);            
  digitalWrite(blinker_rechts, LOW); 
  digitalWrite(bremslicht, LOW); 
  digitalWrite(rueckfahrlicht, LOW);
  digitalWrite(blaues_licht, LOW);
}

int aktorik(){
  //analogvalue_1 = analogRead(xxxx);//Einlesen des Pins vom Tiefpass
  //voltage = referenzvoltage * analogvalue_1; // 5V/1024 = 0.0048V pro Schritt
  //if (voltage < 0.3)//Autonom betrieb
  //{
     //digitalWrite(blaues_licht,LOW); //blaue LED auschalten
     //digitalWrite(xxxxx,On);//Multiplexer Select Pin
     aktorik_node.spinOnce();                                                       //Überprüfung, ob neuer für Knoten neuer Wert vorliegt
     
  //}
  //else  //RC
  /*{
      digitalWrite(blaues_licht,HIGH); //blaue LED anschalten
      //digitalWrite(xxxxx,Off);//Multiplexer Select Pin 
      motor_bewegung_RC_mode(voltage_1);
      
  }*/
  return rc_mode;
  
}

void servo_cb(const std_msgs::Float32& cmd_msg)   //Callback - Funktion für Servoaufruf
{
  servo_bewegung(cmd_msg.data);
}

void motor_cb(const std_msgs::UInt8& cmd_msg)     //Callback - Funktion für Motoraufruf
{
  motor_bewegung(cmd_msg.data);
}

void licht_cb(const std_msgs::UInt8& cmd_msg)     //Callback - Funktion für Lichtaufruf
{
  licht(cmd_msg.data); 
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

void motor_bewegung(byte motor_drehzahl)
{
  if(motor_drehzahl < 0)                                    //rückwärts
  {
    motor_uebertragung = 90 +(0.234 * motor_drehzahl);
  }
  else                                                      //vorwärts
  {
    motor_uebertragung = (0.236 * motor_drehzahl) + 96;
  }
  /* 
   * Übergangsbereich von 91 bis 95 wird nicht betrachtet
   */
 motor.write(motor_uebertragung);
}

void motor_bewegung_RC_mode(float voltage_1)
{
    if (voltage_1 < tiefpass_untere_spannung)                                     //rückwarts
    {
        motor_uebertragung_RC_mode = (voltage_1 * 135.23) + 56.47;
    }
    else if (voltage_1 > tiefpass_obere_spannung)                                 //vorwärts
    {
        motor_uebertragung_RC_mode = (voltage_1 * 135.23) + 58.94;
    }
    else
    {
        motor_uebertragung_RC_mode = 93;
    }
    motor.write(motor_uebertragung_RC_mode);
    
}


void licht(byte led_signal)
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
