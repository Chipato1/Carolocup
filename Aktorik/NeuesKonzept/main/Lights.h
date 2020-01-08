#ifndef Lights_h
#define Lights_h
#include <MyLedMatrix.h>

static const byte head_lights = 53;                       //Den Lichter den Pins zuordnen
static const byte flasher_left = 51;
static const byte flasher_right = 49;
static const byte brake_light = 47;
static const byte reversing_light = 45;
static const byte blue_light = 43

/* für eventuelles Blinken der Lichter
boolean timing_flasher = LOW;
unsigned long previousMillis = 0;
unsigned long interval = 100;
*/
void lights_init();

void licht_leuchti(/*übergabewert*/);









#endif
