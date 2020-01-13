#ifndef Servo_h
#define Servo_h
#define pi 3.141592653589

#include <Servo.h>


Servo servo;
float lenkwinkel_bogenmaß;
float wert_servo;
float lenkwinkel_servosize;

void servo_init();

void servo_bewegung(float lenkwinkel_bogenmaß);






#endif
