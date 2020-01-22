#include <Arduino.h>

const byte frontlicht = 53;                       //Den Lichter die Pins zuordnen
const byte blinker_links = 51;
const byte blinker_rechts = 49;
const byte bremslicht = 47;
const byte rueckfahrlicht = 45;
const byte blaues_licht = 43;

static byte led_signal;
/* für eventuelles Blinken der Lichter
boolean timing_flasher = LOW;
unsigned long previousMillis = 0;
unsigned long interval = 100;
*/
void lights_init();

void licht_leuchti(byte led_signal);
