#ifndef qtr_h
#define qtr_h
#include <QTRSensors.h>

extern QTRSensors qtr_front_left;
extern QTRSensors qtr_front_right;
extern QTRSensors qtr_back_left;
extern QTRSensors qtr_back_right;

extern int** reflective_value;
void init_qtr();
int** read_QTR();
#endif
