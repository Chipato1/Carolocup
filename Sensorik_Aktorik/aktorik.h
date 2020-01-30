<<<<<<< HEAD
#ifndef aktorik_h
#define aktorik_h

#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>

#define referenzvoltage               0.0021259765       //Referenzspannung zur Berechnung der Tiefpassspannung vom Motor - PWM
#define pi                            3.141592653589
#define tiefpass_untere_spannung      1.5       //Schwellwert Spannung am Tiefpass zum rückwertsfahren
#define tiefpass_obere_spannung       2         //Schwellwert Spannung am Tiefpass zum vorwärtsfahren

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

void init_aktorik();
int aktorik();

void servo_cb(const std_msgs::Float32& cmd_msg);
void motor_cb(const std_msgs::UInt16& cmd_msg);
void lichtLinks_cb(const std_msgs::UInt8& light_state);
void lichtRechts_cb(const std_msgs::UInt8& light_state);
void lichtBremse_cb(const std_msgs::UInt8& light_state);
void lichtRemote_cb(const std_msgs::UInt8& light_state);

void servo_bewegung(float lenkwinkel_bogenmass);  //Funktion Servosteuerung im autonomen Betrieb
void motor_bewegung(int8_t motor_drehzahl);         //Funktion Motorsteuerung im autonomen Betrieb
void motor_bewegung_RC_mode (int8_t voltage_1);     //Funktion Motorsteuerung im RC - Mode
void set_led_states();
void set_output(short state, short port);

#endif
=======
#ifndef aktorik_h
#define aktorik_h

#include <Arduino.h>
#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Float32.h>

#define referenzvoltage               0.0021259765       //Referenzspannung zur Berechnung der Tiefpassspannung vom Motor - PWM
#define pi                            3.141592653589
#define tiefpass_untere_spannung      0.24795         //Schwellwert Spannung am Tiefpass zum rückwertsfahren
#define tiefpass_obere_spannung       0.27405         //Schwellwert Spannung am Tiefpass zum vorwärtsfahren
#define rcmode_schwellenwert          0.3             //Schwellwert Spannung an Channel 4 zur Erkennung, dass RC mode aktiv ist (sollte noch angepasst werden)

#define tiefpass_pwm_motor_voltage    A12
#define tiefpass_rcmode               A13
#define tiefpass_pwm_motor_voltage_nr 12
#define tiefpass_rcmode_voltage_nr    13
#define MUX_Select                    48
#define frontlicht                    53
#define blinker_links                 51
#define blinker_rechts                49
#define bremslicht                    47
#define rueckfahrlicht                45
#define blaues_licht                  43

void init_aktorik();
int aktorik();

void servo_cb(const std_msgs::Float32& cmd_msg);
void motor_cb(const std_msgs::UInt16& cmd_msg);
void lichtLinks_cb(const std_msgs::UInt8& light_state);
void lichtRechts_cb(const std_msgs::UInt8& light_state);
void lichtBremse_cb(const std_msgs::UInt8& light_state);
void lichtRemote_cb(const std_msgs::UInt8& light_state);

void servo_bewegung(float lenkwinkel_bogenmass);  //Funktion Servosteuerung im autonomen Betrieb
void motor_bewegung(byte motor_drehzahl);         //Funktion Motorsteuerung im autonomen Betrieb
void motor_bewegung_RC_mode ();                   //Funktion Motorsteuerung im RC - Mode
void set_led_states();
void set_output(int state, int port);

void rcmode_publish(int rc_mode);

#endif
>>>>>>> b963c6853337467e4170f7131b37a4793bf65d89
