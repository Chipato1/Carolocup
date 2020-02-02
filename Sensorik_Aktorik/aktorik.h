#ifndef aktorik_h
#define aktorik_h

#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>

#define referenzvoltage               0.0021259765       //Referenzspannung zur Berechnung der Tiefpassspannung vom Motor - PWM
#define pi                            3.141592653589
#define tiefpass_untere_spannung      1.5                //Schwellwert Spannung am Tiefpass zum rückwertsfahren
#define tiefpass_obere_spannung       2                  //Schwellwert Spannung am Tiefpass zum vorwärtsfahren

#define interval 1000

#define tiefpass_pwm_motor_voltage    A12
#define tiefpass_pwm_motor_voltage_nr 12
#define MUX_Select                    48
#define frontlicht                    53
#define blinker_links                 51
#define blinker_rechts                49
#define bremslicht                    47
#define rueckfahrlicht                45
#define blaues_licht                  43

static Servo servo;
static Servo motor; 

static int8_t state_light_r = 0;
static int8_t state_light_l = 0;
static int8_t state_light_b = 0;
static int8_t state_light_rem = 0;

 
static int8_t rc_mode = 0;
static int16_t analogvalue_1; //eingelesener Pin - Wert am Tiefpass
  
static float wert_servo;
static float lenkwinkel_servosize;
static float lenkwinkel_grad;

static uint16_t previousMillis = 0;
static boolean blinkstate = true;

void init_aktorik();
int aktorik();

void servo_bewegung(float lenkwinkel_bogenmass);     //Funktion Servosteuerung im autonomen Betrieb
void motor_bewegung(int16_t motor_drehzahl);         //Funktion Motorsteuerung im autonomen Betrieb
void motor_bewegung_RC_mode (int16_t voltage_1);     //Funktion Motorsteuerung im RC - Mode
void set_led_states();
void set_output(int8_t state, int8_t port);

#endif
