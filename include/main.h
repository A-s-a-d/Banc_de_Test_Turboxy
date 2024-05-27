#ifndef MAIN_H
#define MAIN_H

/* pin 2 used for pressbutton 1.
pin A2 used for temperature sensor
pin 3 used for current generator 1
pin 4 generate for current generator 2*/

#include <Arduino.h>
#include <Wire.h>
#include "Ticker.h"
#include "Capteur_de_temperature.h"
#include "ADC.h"
#include "START_BUTTON.h"
#include "Turboxy.h"
#include "Courant.h"
#define WIRE Wire

#define interval_wait_get_temperature 500
#define interval_wait_current 2000
bool Test_Temperature_Valid = 0;
bool Test_courant1_Valid = 0;
bool Test_courant2_Valid = 0;
bool test_current_2 = 0;
bool test_current_1 = 0;
uint8_t etape = 0;
float DATA_TEMPERATURE_RECIVED_TURBOXY = 0.0;

#define interval_wait_message_press_button 1000

#endif