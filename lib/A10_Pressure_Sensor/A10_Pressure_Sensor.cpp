#include "A10_Pressure_Sensor.h"

A10_Pressure_Sensor::A10_Pressure_Sensor(/* args */)
{
    _Pressure = 0;
    _Num_VADC_PRESSURE = 0;
    _Voltage = 0;
}

uint16_t A10_Pressure_Sensor::get_ADC_num()
{
    _Num_VADC_PRESSURE = analogRead(PIN_Analog_capteur_pression);
}
float A10_Pressure_Sensor::get_voltage()
{
    _Voltage = quantum_ADC * _Num_VADC_PRESSURE; // variable qui stocke la valeur de tension lu.
}
float A10_Pressure_Sensor::get_pressure_Bar()
{
    get_ADC_num();
    delay(1);
    get_voltage();
    delay(1);
    _Pressure = (_Voltage * 1.21212121) - 1.01325;
    return _Pressure;
}