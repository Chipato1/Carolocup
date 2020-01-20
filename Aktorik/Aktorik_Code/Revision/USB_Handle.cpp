#include "USB_Handle.h"

void usb_init()
{
  servo_init();
  ligths_init();
  motor_init();
  aktorik_knoten.initNode();
  aktorik_knoten.subscribe(sub_servo);
  aktorik_knoten.subscribe(sub_motor);
  aktorik_knoten.subscribe(sub_licht);
 
}

void servo_cb(const std_msgs::Float32& cmd_msg)
{
  servo_bewegung(cmd_msg.data);
}

void motor_cb(const std_msgs::UInt8& cmd_msg)
{
  motor_bewegung(cmd_msg.data);
}

void licht_cb(const std_msgs::UInt8& cmd_msg)
{
  licht_leuchti(cmd_msg.data); 
}



   /*
  union prot
  {
    int arr[3];

    struct protocol
    {
      int id;
      int value;
      int value2;
    }
  }
  */
