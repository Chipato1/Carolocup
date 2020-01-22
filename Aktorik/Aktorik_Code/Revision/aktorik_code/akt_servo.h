
#include <Servo.h>
#define pi 3.141592653589

static Servo servo_servo;

static float lenkwinkel_bogenmass;
static float wert_servo;
static float lenkwinkel_servosize;
static float lenkwinkel_grad;

void servo_init();

void servo_bewegung(float lenkwinkel_bogenmass);
