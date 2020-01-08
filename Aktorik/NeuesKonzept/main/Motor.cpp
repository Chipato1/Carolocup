#include "Motor.h"

void motor_init()
{
  motor.attach(10);
}

void motor_bewegung(/*übergabewert*/)
{
  /* 
   * Berechnung des tatsächlichen Wertes bzw. lookup-tabelle (übergabewert -> wert_motor)
   * Übergangsbereich von 91 bis 95
   */
  motor.write(/*wert_motor*/); //Motor passt sich dem Parameter an
}
