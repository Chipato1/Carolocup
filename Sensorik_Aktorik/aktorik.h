#ifndef aktorik_h
#define aktorik_h

#include <Arduino.h>
#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Float32.h>

#define referenzvoltage 0.0021259765       //Referenzspannung zur Berechnung der Tiefpassspannung vom Motor - PWM
#define pi 3.141592653589
#define tiefpass_untere_spannung  1.5       //Schwellwert Spannung am Tiefpass zum rückwertsfahren
#define tiefpass_obere_spannung   2         //Schwellwert Spannung am Tiefpass zum vorwärtsfahren

void init_aktorik();
int aktorik();

void servo_cb(const std_msgs::Float32& cmd_msg);
void motor_cb(const std_msgs::UInt8& cmd_msg);
void licht_cb(const std_msgs::UInt8& cmd_msg);

void servo_bewegung(float lenkwinkel_bogenmass);  //Funktion Servosteuerung im autonomen Betrieb
void motor_bewegung(byte motor_drehzahl);         //Funktion Motorsteuerung im autonomen Betrieb
void motor_bewegung_RC_mode (byte voltage_1);     //Funktion Motorsteuerung im RC - Mode
void licht(byte led_signal);                      //Funktion Lichtanlage steuern

#endif
