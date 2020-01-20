#include <Servo.h>

#define byte uint8_t

Servo motor;

byte motor_drehzahl;
byte motor_uebertragung;
byte motor_uebertragung_RC_mode;

void motor_init();

void motor_bewegung(byte motor_drehzahl);

void motor_bewegung_RC_mode (byte voltage_1);

