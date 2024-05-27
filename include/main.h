#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <Wire.h>
#include "Ticker.h"
#include "Capteur_de_temperature.h"
#include "ADC.h"
#include "START_BUTTON.h"
#include "Turboxy.h"
#define WIRE Wire

#define interval_wait_get_temperature 500
bool Test_Temperature_Valid = 0;
uint8_t etape = 0;
float DATA_TEMPERATURE_RECIVED_TURBOXY = 0.0;

#define interval_wait_message_press_button 1000

#endif