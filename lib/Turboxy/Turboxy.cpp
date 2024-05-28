#include "Turboxy.h"

Turboxy::Turboxy(/* args */)
{
    for (uint8_t i = 0; i <= 5; i++)
    {
        _table_data_TURBOXY[i] = 0; // Tableau pour stocker les donnees recu par TURBOXY
    }
    // 1st DATA = 0x56 = data type
    _DATA_TYPE_RECIVED_TURBOXY = 0;
    // 2nd & 3rd DATA = Chlore in µA
    _DATA_CHLORE_RECIVED_TURBOXY = 0;
    // 4th DATA = Frequency in Hz
    _DATA_FREQUENCY_RECIVED_TURBOXY = 0;
    // 5th DATA = Temperature * 2
    _DATA_TEMPERATURE_RECIVED_TURBOXY = 0;
}

bool Turboxy::_Turboxy_test_communication()
{
    bool error_code; // 0 si erreur et 1 si com ok
    Wire.beginTransmission(adress_write);
    Wire.write(0x4D);
    uint8_t error = Wire.endTransmission();
    if (error == 0)
    {

        Serial.println("\t communication ok at 0x01");
        error_code = 1;
    }
    else
    {
        // Serial.print(error);
        // Serial.println("\t communication error at 0x01");
        error_code = 0;
    }
    return error_code;
}

void Turboxy::Turboxy_Display_data()
{
    Serial.print("DATA : ");
    for (uint8_t i = 0; i < 5; i++)
    {
        uint8_t data = _table_data_TURBOXY[i];
        Serial.print(" 0X");
        Serial.print(data, HEX);
    }
    Serial.println("");
    Serial.print("DATA TYPE = 0x");
    Serial.print(_DATA_TYPE_RECIVED_TURBOXY, HEX);
    Serial.print("\tCHLORE = ");
    Serial.print(_DATA_CHLORE_RECIVED_TURBOXY);
    Serial.print("\tFREQUENCY = ");
    Serial.print(_DATA_FREQUENCY_RECIVED_TURBOXY);
    Serial.print("\tTEMPERATURE = ");
    Serial.print(_DATA_TEMPERATURE_RECIVED_TURBOXY, 2);
    Serial.println("\tend DATA");
}

void Turboxy::_Turboxy_get_data()
{
    uint8_t error = 0x00;
    uint8_t error_count = 0x00;
    _Turboxy_test_communication();
    delay(10);
    if (error_count <= 5)
    {
        Wire.requestFrom(adress_write, 5);
        _table_data_TURBOXY[0] = Wire.read();
        _table_data_TURBOXY[1] = Wire.read();
        _table_data_TURBOXY[2] = Wire.read();
        _table_data_TURBOXY[3] = Wire.read();
        _table_data_TURBOXY[4] = Wire.read();
        error = Wire.endTransmission();
        _DATA_TYPE_RECIVED_TURBOXY = _table_data_TURBOXY[0];
        _DATA_CHLORE_RECIVED_TURBOXY = (_table_data_TURBOXY[1] << 8) + _table_data_TURBOXY[2];
        _DATA_FREQUENCY_RECIVED_TURBOXY = _table_data_TURBOXY[3];
        _DATA_TEMPERATURE_RECIVED_TURBOXY = _table_data_TURBOXY[4] / 2.0;
        if (error == 0)
        {
            Serial.println("Communication ok at  Turboxy recive data 0x02");
            error = 0xFF;
            error_count = 6;
        }
        else
        {
            _DATA_TYPE_RECIVED_TURBOXY = error_data_type;
            _DATA_CHLORE_RECIVED_TURBOXY = error_chlore;
            _DATA_FREQUENCY_RECIVED_TURBOXY = error_frequency;
            _DATA_TEMPERATURE_RECIVED_TURBOXY = error_temperature;
            Serial.println(" communication error Turboxy recive data or other error ");
            error_count++;
            delay(100);
        }
    }
}

void Turboxy::Turboxy_Accquire_data()
{
    _Turboxy_get_data();
}

uint8_t Turboxy::GET_TYPE()
{
    _Turboxy_get_data();
    return _DATA_TYPE_RECIVED_TURBOXY;
}

float Turboxy::GET_CHLORE()
{
    _Turboxy_get_data();
    return _DATA_CHLORE_RECIVED_TURBOXY;
}

uint8_t Turboxy::GET_FREQUENCY()
{
    _Turboxy_get_data();
    return _DATA_FREQUENCY_RECIVED_TURBOXY;
}

float Turboxy::GET_TEMPERATURE()
{

    _Turboxy_get_data();
    return _DATA_TEMPERATURE_RECIVED_TURBOXY;
}