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
#include "Adafruit_SSD1306.h"
#include "OLED.h"
#define WIRE Wire

#define interval_wait_get_temperature 2000
#define interval_wait_current 1000
#define nbr_de_mesures_courant 10
#define tolerence_courant 10

bool Test_Temperature_Valid = 0;

uint8_t etape_test_I_T = 0;
uint8_t etape_test_flux = 0;
bool problem_com_turboxy = 0;
bool validation_courant_finale = 0;

#define interval_display 1000

float DATA_TEMPERATURE_RECIVED_TURBOXY = 0.0;

#define interval_wait_message_press_button 1000
#define interval_wait_message_pressure_button 500

#define interval_wait_pressure_increase 1000
#define interval_wait_pressure 1000
#define interval_wait_positioning_valves 3000

#define nbr_of_pressur_test 10

struct pressure_delta
{
    float pressure_start;
    float pressure_end;
    float delta;
    bool pression_valid;

    /* data */
} pressure_delta;

struct freq_test
{
    float frequency[10]; // Array to store frequency values;
    uint8_t reference = 50;
    bool valid = 0;
    const uint8_t delta_reference = 20;
    uint8_t delta;
    uint8_t testCount = 0;
} freq_test;

struct temperature
{
    bool valid = false;
    uint8_t nbr_valid = 0;
} temperature;

struct courant2
{
    const uint8_t nbr_values = nbr_de_mesures_courant;
    float tableval[10];
    float moyenne;
    bool validation_courant_2_finale = 0;
    float Courant2_Reference_test = 0;
    bool Test_courant2_Valid = 0;
    bool test_current_2 = 0;
    float somme_moyenne_courant_2 = 0;
} courant2;

struct courant1
{
    const uint8_t nbr_values = nbr_de_mesures_courant;
    float tableval[11];
    float moyenne;
    bool validation_courant_1_finale = 0;
    float Courant1_Reference_test = 0;
    bool Test_courant1_Valid = 0;
    bool test_current_1 = 0;

} courant1;
void moyenne(float table[], uint8_t nbr_valeurs);

#define interval_wait_pressure_display 1000;

#endif