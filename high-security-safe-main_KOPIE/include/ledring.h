#ifndef LEDRING_H
#define LEDRING_H

#include <inttypes.h>
#include "Arduino.h"
#include "pin_defs.h"
#include <iostream>
#include <algorithm>
#include <Adafruit_NeoPixel.h>
#include "rotary_encoder.h"

// Deklariere die Variablen als extern, damit sie in main.cpp verwendet werden können
extern uint32_t btn_state;
extern int btn_counter;
extern int selectedNumber;
extern int eingabeArrayMain[3];
extern int eingabeArrayMainIndex;
extern int vorgabeCodeArrayMain[3];

// Prototypen der Funktionen
void led_ring_setup();
void verbindung(int selectedNumber);
void arrayVergleich();
void setLEDColorAusgabe(int pixel, int red, int green, int blue);
void clearLEDs();


#endif //LEDRING_H 