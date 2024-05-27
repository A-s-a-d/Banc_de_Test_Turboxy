#ifndef COURANT_H
#define COURANT_H

#include <Arduino.h>
#define pin_current_1 3
#define pin_current_2 4
#define value_5V 4.8

class Courant
{
private:
public:
    Courant(/* args */);
    void begin(uint64_t resistance_1, uint64_t resistance_2);
    float ohm_law_i(float voltage, uint64_t Resistance);
    void calculate_current();
    void Gen_courant_1_start();
    void Gen_courant_1_stop();
    void Gen_courant_2_start();
    void Gen_courant_2_stop();
    float get_courant_1();
    float get_courant_2();

    uint64_t resistance_R1;
    uint64_t resistance_R2;
    float value_current_1;
    float value_current_2;
};

#endif