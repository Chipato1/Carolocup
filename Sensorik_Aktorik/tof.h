#ifndef tof_h
#define tof_h
#include "Adafruit_VL6180X.h"
#include "Adafruit_VL53L0X.h"


//addresses for ToF sensors
#define ToF_front_ADDRESS 0x30
#define ToF_left_ADDRESS  0x31
#define ToF_right_ADDRESS 0x32
#define ToF_cross_ADDRESS 0x33


//shutdown pins for ToF sensors
#define ToF_front_SHT     25
#define ToF_left_SHT      27
#define ToF_right_SHT     29
#define ToF_cross_SHT     31
#define ToF_back_SHT      33

#define threshold_front   1000
#define threshold_left    1000
#define threshold_right   1000
#define threshold_cross   1000
#define threshold_back    200

const Adafruit_VL53L0X ToF_front  = Adafruit_VL53L0X();
const Adafruit_VL53L0X ToF_left   = Adafruit_VL53L0X();
const Adafruit_VL53L0X ToF_right  = Adafruit_VL53L0X();
const Adafruit_VL53L0X ToF_cross  = Adafruit_VL53L0X();
const Adafruit_VL6180X ToF_back   = Adafruit_VL6180X();

void init_tof();
int8_t* read_TOF();


#endif
