#include "Motor.h"

void motor_init()
{
  motor.attach(10);
}

void motor_bewegung(byte motor_drehzahl)
{
  if(motor_drehzahl < 0)                                    //rückwärts
  {
    motor_uebertragung = 90 -(0.234 * motor_drehzahl);
  }
  else                                                      //vorwärts
  {
    motor_uebertragung = (0.236 * motor_drehzahl) + 96;
  }
  /* 
   * Übergangsbereich von 91 bis 95 wird nicht betrachtet
   */
 motor.write(motor_uebertragung);
}

void motor_bewegung_RC_mode(byte voltage_1)
{
    if (voltage_1 < 2,5 )                                     //rückwarts
    {
        motor_uebertragung_RC_mode = (voltage_1 * 8,33) + 70;
    }
    else if (voltage_1 > 2,5)                                 //vorwärts
    {
        motor_uebertragung_RC_mode = (voltage_1 * 8,33) + 64,35;
    }
    else
    {
        motor_uebertragung_RC_mode = 93;
    }
    motor.write(motor_uebertragung_RC_mode);
    
}
