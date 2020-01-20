#include "USB_Handle.h"

void usb_init()
{
  Serial.begin(9600);
  Serial.println("Verbindung ist aufgebaut");

  aktorik_knoten.initNode();
  aktorik_knoten.subscribe(sub_aktorik);
 
}

void servo_cb(const std_msgs::UInt16& cmd_msg)
{
  servo_bewegung(cmd_msg.data);
}

void motor_cb(const std_msgs::UInt16& cmd_msg)
{
  motor_bewegung(cmd_msg.data);
}

void licht_cb(const std_msgs::UInt16& cmd_msg)
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
