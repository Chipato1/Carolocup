#include "tof.h"

static uint16_t tof_array[5] = {threshold_front,
                                threshold_left,
                                threshold_right,
                                threshold_cross,
                                threshold_back};

void init_tof()
{
  Wire.begin();

  //configure interrupt pins
  pinMode(ToF_front_GPIO,INPUT);
  pinMode(ToF_left_GPIO,INPUT);
  pinMode(ToF_right_GPIO,INPUT);
  pinMode(ToF_cross_GPIO,INPUT);
  pinMode(ToF_back_GPIO,INPUT);

  //configure shutdown pins
  pinMode(ToF_front_SHT,OUTPUT);
  pinMode(ToF_left_SHT,OUTPUT);
  pinMode(ToF_right_SHT,OUTPUT);
  pinMode(ToF_cross_SHT,OUTPUT);
  pinMode(ToF_back_SHT,OUTPUT);
  
  //reset all
  digitalWrite(ToF_front_SHT,LOW);
  digitalWrite(ToF_left_SHT,LOW);
  digitalWrite(ToF_right_SHT,LOW);
  digitalWrite(ToF_cross_SHT,LOW);
  digitalWrite(ToF_back_SHT,LOW);
  delay(1);
  //unreset all
  digitalWrite(ToF_front_SHT,HIGH);
  digitalWrite(ToF_left_SHT,HIGH);
  digitalWrite(ToF_right_SHT,HIGH);
  digitalWrite(ToF_cross_SHT,HIGH);
  digitalWrite(ToF_back_SHT,HIGH);
  delay(1);
  //reset all
  digitalWrite(ToF_front_SHT,LOW);
  digitalWrite(ToF_left_SHT,LOW);
  digitalWrite(ToF_right_SHT,LOW);
  digitalWrite(ToF_cross_SHT,LOW);
  digitalWrite(ToF_back_SHT,LOW);
  delay(1);  

  // set I2C addresses
  digitalWrite(ToF_front_SHT,HIGH);
  delay(1);//wichtig
  ToF_front.setAddress(ToF_front_ADDRESS);
  digitalWrite(ToF_left_SHT,HIGH);
  delay(1);//wichtig
  ToF_left.setAddress(ToF_left_ADDRESS);
  digitalWrite(ToF_right_SHT,HIGH);
  delay(1);//wichtig
  ToF_right.setAddress(ToF_right_ADDRESS);
  digitalWrite(ToF_cross_SHT,HIGH);
  delay(1);//wichtig
  ToF_cross.setAddress(ToF_cross_ADDRESS);
  digitalWrite(ToF_back_SHT,HIGH);
  delay(1);//wichtig
  ToF_back.setAddress(ToF_back_ADDRESS);
  
  ToF_front.init();
  ToF_left.init();
  ToF_right.init();
  ToF_cross.init();
  ToF_back.init();

  ToF_front.setTimeout(500);
  ToF_left.setTimeout(500);
  ToF_right.setTimeout(500);
  ToF_cross.setTimeout(500);
  ToF_back.setTimeout(500);

  ToF_front.startContinuous(50);
  ToF_left.startContinuous(50);
  ToF_right.startContinuous(50);
  ToF_cross.startContinuous(50);
  ToF_back.startContinuous(50);
}

uint16_t* read_TOF()
{  
  if(digitalRead(ToF_front_GPIO)==LOW)
  {
    tof_array[0] = ToF_front.readReg16Bit(ToF_front.RESULT_RANGE_STATUS + 10);
    ToF_front.writeReg(ToF_front.SYSTEM_INTERRUPT_CLEAR, 0x01);
  }

  if(digitalRead(ToF_left_GPIO)==LOW)
  {
    tof_array[1] = ToF_left.readReg16Bit(ToF_left.RESULT_RANGE_STATUS + 10);
    ToF_left.writeReg(ToF_left.SYSTEM_INTERRUPT_CLEAR, 0x01);
  }

  if(digitalRead(ToF_right_GPIO)==LOW)
  {
    tof_array[2] = ToF_right.readReg16Bit(ToF_right.RESULT_RANGE_STATUS + 10);
    ToF_right.writeReg(ToF_right.SYSTEM_INTERRUPT_CLEAR, 0x01);
  }

  if(digitalRead(ToF_cross_GPIO)==LOW)
  {
    tof_array[3] = ToF_cross.readReg16Bit(ToF_cross.RESULT_RANGE_STATUS + 10);
    ToF_cross.writeReg(ToF_cross.SYSTEM_INTERRUPT_CLEAR, 0x01);
  }
  
  if(digitalRead(ToF_back_GPIO)==LOW)
  {
    tof_array[4] = ToF_back.readReg16Bit(ToF_back.RESULT_RANGE_STATUS + 10);
    ToF_back.writeReg(ToF_back.SYSTEM_INTERRUPT_CLEAR, 0x01);
  }
  
  if (tof_array[0] > threshold_front) tof_array[0] = threshold_front;
  if (tof_array[1] > threshold_left) tof_array[1] = threshold_left;
  if (tof_array[2] > threshold_right) tof_array[2] = threshold_right;
  if (tof_array[3] > threshold_cross) tof_array[3] = threshold_cross;
  if (tof_array[4] > threshold_back) tof_array[4] = threshold_back;
  
  return tof_array;
}
