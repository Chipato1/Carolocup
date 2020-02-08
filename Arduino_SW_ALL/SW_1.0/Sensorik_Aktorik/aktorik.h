#ifndef aktorik_h
#define aktorik_h


#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Int16.h>
#include <std_msgs/UInt64.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>

#define referenzvoltage               0.0021259765        //Referenzspannung zur Berechnung der Tiefpassspannung vom Motor - PWM
#define pi                            3.141592653589
#define tiefpass_untere_spannung      35                  //Schwellwert Spannung am Tiefpass zum rückwertsfahren
#define tiefpass_obere_spannung       53                  //Schwellwert Spannung am Tiefpass zum vorwärtsfahren
#define rcmode_schwellenwert          50                  //Schwellwert Spannung an Channel 4 zur Erkennung, dass RC mode aktiv ist
#define servo_Steigung_kleinerNull    1.11111
#define servo_Steigung_groesserNull   1.4
#define servo_nullstellung_PWM        88
#define interval 500

#define pwm_fernbedienung_servo       8
#define pwm_fernbedienung_motor       4
#define tiefpass_rcmode_voltage       A13
#define tiefpass_rcmode_voltage_nr    13
#define frontlicht                    34
#define blinker_links                 38
#define blinker_rechts                40
#define bremslicht                    36
#define rueckfahrlicht                32
#define blaues_licht                  42
#define drive_mode_off                43
#define drive_mode_freeDrive          45
#define drive_mode_obstacleAvoidance  47

void init_aktorik(ros::NodeHandle *aktorik_node);
bool aktorik();

void servo_cb(const std_msgs::Float32& cmd_msg);
void motor_cb(const std_msgs::Int16& cmd_msg);
void lichtLinks_cb(const std_msgs::UInt8& light_state);
void lichtRechts_cb(const std_msgs::UInt8& light_state);
void lichtBremse_cb(const std_msgs::UInt8& light_state);
void lichtRemote_cb(const std_msgs::UInt8& light_state);
void lichtRueck_cb(const std_msgs::UInt8& light_state);

void servo_bewegung(float lenkwinkel_bogenmass);  //Funktion Servosteuerung im autonomen Betrieb
void motor_bewegung(int16_t motor_drehzahl);      //Funktion Motorsteuerung im autonomen Betrieb
void motor_bewegung_RC_mode ();                  //Funktion Motorsteuerung im RC - Mode
void servo_bewegung_RC_mode ();
void set_led_states();
void set_output(short state, short port);

void rc_publish();
void drive_mode_publish();
void t_test_publish(unsigned long value);

#endif
