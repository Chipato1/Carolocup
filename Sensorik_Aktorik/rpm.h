#ifndef rpm_h
#define rpm_h

#include <Encoder.h>

#define ticks_per_cycle 9

static Encoder right_encoder(2, 3);
static Encoder left_encoder(18, 19);

static float rpm_value;

static int RPM_left, RPM_timer_left;
static int old_left;

static int RPM_right, RPM_timer_right;
static int old_right;


void init_rpm();
float read_RPM();

#endif
