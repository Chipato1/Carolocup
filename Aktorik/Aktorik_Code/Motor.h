#ifndef Motor_h
#define Motor_h
#include <Servo.h>

Servo motor;

byte motor_drehzahl;
byte motor_uebertragung;
byte motor_uebertragung_RC_mode;

void motor_init();

void motor_bewegung(byte motor_drehzahl);

void motor_bewegung_RC_mode (voltage_1);










#endif
