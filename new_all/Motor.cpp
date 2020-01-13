#include "Motor.h"

void motor_init()
{
  motor.attach(10);
}

void motor_bewegung(byte motor_drehzahl)
{
  if(motor_drehzahl<0)//Rückwärts
  {
    motor_uebertragung = 90 -(0.234 * motor_drehzahl);
  }
  else//Vorwärts
  {
    motor_uebertragung = (0.236 * motor_drehzahl) + 96;
  }
  /* 
   * Übergangsbereich von 91 bis 95 wird nicht betrachtet
   */
 motor.write(motor_uebertragung);
}
