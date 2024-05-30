#ifndef A10_PRESSURE_SENSOR
#define A10_PRESSURE_SENSOR

#include <Arduino.h>
#include "ADC.h"

#define PIN_Analog_capteur_pression A1 // PIN ADC

class A10_Pressure_Sensor
{
private:
    float _Pressure;
    uint16_t _Num_VADC_PRESSURE; // variable qui stocke la valeur envoyé sur ADC
    float _Voltage;

public:
    A10_Pressure_Sensor(/* args */);
    uint16_t get_ADC_num();
    float get_voltage();
    float get_pressure_Bar();
};

#endif