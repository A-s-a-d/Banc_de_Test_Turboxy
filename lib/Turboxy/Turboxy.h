#ifndef Turboxy_H
#define Turboxy_H

#include <Arduino.h>
#include <Wire.h>

#define WIRE Wire

#define adress_write 0x01
#define adress_read 0x02

#define error_temperature -1
#define error_chlore -1
#define error_frequency 0xFF
#define error_data_type 0xFF
#define offset 5000

class Turboxy
{
private:
    bool _Turboxy_test_communication();
    void _Turboxy_get_data();

    uint8_t _table_data_TURBOXY[5]; // Tableau pour stocker les donnees recu par TURBOXY
    // 1st DATA = 0x56 = data type
    uint8_t _DATA_TYPE_RECIVED_TURBOXY;
    // 2nd & 3rd DATA = Chlore in µA
    float _DATA_CHLORE_RECIVED_TURBOXY;
    // 4th DATA = Frequency in Hz
    uint8_t _DATA_FREQUENCY_RECIVED_TURBOXY;
    // 5th DATA = Temperature * 2
    float _DATA_TEMPERATURE_RECIVED_TURBOXY;

    /* data */
public:
    Turboxy(/* args */);
    void Turboxy_Display_data();
    void Turboxy_Accquire_data();
    bool begin();

    uint8_t GET_TYPE();
    float GET_CHLORE();
    uint8_t GET_FREQUENCY();
    float GET_TEMPERATURE();
};

#endif