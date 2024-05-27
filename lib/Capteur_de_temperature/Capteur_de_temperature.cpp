#include "Capteur_de_temperature.h"

Capteur_de_temperature::Capteur_de_temperature(/* args */)
{
    _temperature = 0;
}

Capteur_de_temperature::~Capteur_de_temperature()
{
}

float Capteur_de_temperature::GetTemperature()
{
    uint16_t Num_VADC_Temperature = 0; // variable qui stocke la valeur envoyé sur ADC
    Num_VADC_Temperature = analogRead(PIN_VADC_Temperature);
    float mVout = quantum_ADC * Num_VADC_Temperature; // variable qui stocke la valeur de tension lu.
    float Temperature_kelvin = mVout / 10;
    float Temperature_celcius = Temperature_kelvin - 273.15;
    _temperature = Temperature_celcius;
    return Temperature_celcius;
}

void Capteur_de_temperature::display_temp_Serial()
{
    Serial.print("la Temperature de capteur est ");
    Serial.println(_temperature);
}