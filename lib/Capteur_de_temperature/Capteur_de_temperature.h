#ifndef CAPTEUR_DE_TEMPERATURE_H
#define CAPTEUR_DE_TEMPERATURE_H

#include <Arduino.h>
#include "ADC.h"

#define PIN_VADC_Temperature A2 // PIN ADC

class Capteur_de_temperature
{
private:
    float _temperature;
public:
    Capteur_de_temperature(/* args */);
    ~Capteur_de_temperature(); // destructor
    float GetTemperature();
    void display_temp_Serial();
};

#endif