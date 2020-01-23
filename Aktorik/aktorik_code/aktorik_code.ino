//Präprozessor Anweisungen

//Includes
#include <Arduino.h>
#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Float32.h>

#define referenzvolatage 0.0021259765       //Referenzspannung zur Berechnung der Tiefpassspannung vom Motor - PWM
#define pi 3.141592653589
#define tiefpass_untere_spannung XXX        //Schwellwert Spannung am Tiefpass zum rückwertsfahren
#define tiefpass_obere_spannung XXX         //Schwellwert Spannung am Tiefpass zum vorwärtsfahren

float voltage_1;                            //Spannung Tiefpass vom Motor - PWM
int analogvalue_1;                          //eingelesener Pin - Wert am Tiefpass
  
float lenkwinkel_bogenmass;                 //
float wert_servo;                           //
float lenkwinkel_servosize;                 //
float lenkwinkel_grad;                      //

byte motor_drehzahl;                        //
byte motor_uebertragung;                    //
byte motor_uebertragung_RC_mode;            //

const byte frontlicht = 53;                 //Pinbelegung der LEDs
const byte blinker_links = 51;
const byte blinker_rechts = 49;
const byte bremslicht = 47;
const byte rueckfahrlicht = 45;
const byte blaues_licht = 43;


void servo_bewegung(float lenkwinkel_bogenmass);  //Funktion Servosteuerung im autonomen Betrieb

void motor_bewegung(byte motor_drehzahl);         //Funktion Motorsteuerung im autonomen Betrieb
void motor_bewegung_RC_mode (byte voltage_1);     //Funktion Motorsteuerung im RC - Mode

void licht_leuchti(byte led_signal);              //Funktion Lichtanlage steuern


ros::NodeHandle aktorik_knoten;                   //Initialisierung des ROS - Knoten

Servo servo;                                      //
Servo motor;                                      //

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
  licht_leuchti(cmd_msg.data); 
}

ros::Subscriber<std_msgs::Float32> sub_servo("servo", servo_cb);  //Deklaration von Servo - Topic
ros::Subscriber<std_msgs::UInt8> sub_motor("motor", motor_cb);    //Deklaration von Motor - Topic
ros::Subscriber<std_msgs::UInt8> sub_licht("licht", licht_cb);    //Deklaration von Licht - Topic



void setup()  //Setup - Funktion
{
  aktorik_knoten.initNode();  //Initialisierung des ROS - Knoten
  
  aktorik_knoten.subscribe(sub_servo);  //Zuweisung Servo Subscriber zum Aktorik - Knoten
  aktorik_knoten.subscribe(sub_motor);  //Zuweisung Motor Subscriber zum Aktorik - Knoten
  aktorik_knoten.subscribe(sub_licht);  //Zuweisung Licht Subscriber zum Aktorik - Knoten

  motor.attach(12); //Motor an Pin zuweisen

  servo.attach(11); //Servo an Pin zuweisen

  pinMode(frontlicht, OUTPUT);              //Setzen der Lichter als Ausgang
  pinMode(blinker_links, OUTPUT);         
  pinMode(blinker_rechts, OUTPUT);        
  pinMode(bremslicht, OUTPUT);              
  pinMode(rueckfahrlicht, OUTPUT);          
  pinMode(blaues_licht, OUTPUT);

  digitalWrite(blinker_links,LOW);            //Alle Lichter ausschalten
  digitalWrite(blinker_rechts,LOW); 
  digitalWrite(bremslicht,LOW); 
  digitalWrite(rueckfahrlicht,LOW);
  digitalWrite(blaues_licht, LOW);

}


void loop() //Funktionsschleife
{
  
  //analogvalue_1 = analogRead(xxxx);//Einlesen des Pins vom Tiefpass
  //voltage_1 = referenzvolatage * analogvalue_1; // 5V/1024 = 0.0048V pro Schritt
  //if (voltage_1 < 0.3)//Autonom betrieb
  //{
     //digitalWrite(blaues_licht,LOW); //blaue LED auschalten
     //digitalWrite(xxxxx,On);//Multiplexer Select Pin
     aktorik_knoten.spinOnce();                                                       //Überprüfung, ob neuer für Knoten neuer Wert vorliegt
     
  //}
  //else  //RC
  /*{
      digitalWrite(blaues_licht,HIGH); //blaue LED anschalten
      //digitalWrite(xxxxx,Off);//Multiplexer Select Pin 
      motor_bewegung_RC_mode(voltage_1);
      
  }*/

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
        motor_uebertragung_RC_mode = (voltage_1 * 8.33) + 70;
    }
    else if (voltage_1 > tiefpass_obere_spannung)                                 //vorwärts
    {
        motor_uebertragung_RC_mode = (voltage_1 * 8.33) + 74.432;
    }
    else
    {
        motor_uebertragung_RC_mode = 93;
    }
    motor.write(motor_uebertragung_RC_mode);
    
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
