#ifndef Motor_h
#define Motor_h
#include <Servo.h>

Servo motor;

byte motor_drehzahl;
byte motor_uebertragung;

void motor_init();

void motor_bewegung(byte motor_drehzahl);










#endif
