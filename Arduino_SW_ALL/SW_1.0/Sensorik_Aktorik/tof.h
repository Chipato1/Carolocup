#ifndef tof_h
#define tof_h
//#include "Adafruit_VL6180X.h"
//#include "Adafruit_VL53L0X.h"
#include <Wire.h>
#include <VL53L0X.h>

//addresses for ToF sensors
#define ToF_front_ADDRESS 0x30
#define ToF_left_ADDRESS  0x31
#define ToF_right_ADDRESS 0x32
#define ToF_cross_ADDRESS 0x33
#define ToF_back_ADDRESS  0x34

//shutdown pins for ToF sensors
#define ToF_front_SHT     25
#define ToF_left_SHT      27
#define ToF_right_SHT     29
#define ToF_cross_SHT     31
#define ToF_back_SHT      33

//interrupt pins for ToF sensors
#define ToF_front_GPIO    14
#define ToF_left_GPIO     15
#define ToF_right_GPIO    16
#define ToF_cross_GPIO    17
#define ToF_back_GPIO     18

#define threshold_front   1000
#define threshold_left    1000
#define threshold_right   1000
#define threshold_cross   1000
#define threshold_back    200

const VL53L0X ToF_front;
const VL53L0X ToF_left;
const VL53L0X ToF_right;
const VL53L0X ToF_cross;
const VL53L0X ToF_back;

void init_tof();
uint16_t* read_TOF();

#endif
