#include <Servo.h>
#include "Lights.h"
#include "Motor.h"
#include "ParameterControl.h"
#include "Servo.h"
#include "USB_Handle"


void setup() 
{
  lights_init();
  servo_init();
  motor_init();
  usb_init();
}

void loop() 
{
  hoden_knoten.spinOnce();
}
