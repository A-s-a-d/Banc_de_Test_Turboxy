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
#include "Servo_rack.h"
#include "Button_pression.h"
#include "valve.h"
#include "A10_Pressure_Sensor.h"
#define WIRE Wire

#define interval_wait_get_temperature 500
#define interval_wait_current 500

bool Test_Temperature_Valid = 0;
bool Test_courant1_Valid = 0;
bool Test_courant2_Valid = 0;
bool test_current_2 = 0;
bool test_current_1 = 0;
uint8_t etape_test_I_T = 0;
uint8_t etape_test_flux = 0;

float DATA_TEMPERATURE_RECIVED_TURBOXY = 0.0;

#define interval_wait_message_press_button 1000
#define interval_wait_message_pressure_button 500

#define interval_wait_pressure_increase 10000
#define interval_wait_pressure 10000
#define interval_wait_positioning_valves 10000

#define servo_position_repos 15
#define servo_position_test 20
#endif