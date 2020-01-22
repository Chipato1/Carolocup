#include <Servo.h>

#define byte uint8_t

static Servo servo_motor;

static byte motor_drehzahl;
static byte motor_uebertragung;
static byte motor_uebertragung_RC_mode;

void motor_init();

void motor_bewegung(byte motor_drehzahl);

void motor_bewegung_RC_mode (byte voltage_1);
