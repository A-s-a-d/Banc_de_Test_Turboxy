#include "A10_Pressure_Sensor.h"

A10_Pressure_Sensor::A10_Pressure_Sensor(/* args */)
{
    _Pressure = 0;
    _Num_VADC_PRESSURE = 0;
    _Voltage_mV = 0;
}

uint16_t A10_Pressure_Sensor::get_ADC_num()
{
    _Num_VADC_PRESSURE = analogRead(PIN_Analog_capteur_pression);
}
float A10_Pressure_Sensor::get_Voltage_mV()
{
    _Voltage_mV = quantum_ADC * _Num_VADC_PRESSURE; // variable qui stocke la valeur de tension lu.
}
float A10_Pressure_Sensor::get_pressure_mBar()
{
    get_ADC_num();
    delay(1);
    get_Voltage_mV();
    delay(1);
    _Pressure = (_Voltage_mV * 1.224365 - atmospheric_pressure);
    return _Pressure;
}