#include "Servo.h"

void servo_init()
{
  servo.attach(9);
}

void servo_bewegung(/*übergabewert*/)
{
  if(/*übergabewert*/ > 64 and /*übergabewert*/ < 115) //anpassung der grenzen
  {
    /* falls Übergabe zw. -20°(links) und +20°(rechts):
     * 
     * wert_servo = 0.95 * übergabewert + 96;
     */
     
    servo.write(/*wert_servo*/); //Servo fährt in die ensprechende Stellung
  }
}
