#include <Courant.h>

Courant::Courant(/* args */)
{
}

void Courant::begin(uint64_t resistance_1, uint64_t resistance_2)
{
    pinMode(pin_current_1, OUTPUT);
    pinMode(pin_current_2, OUTPUT);
    Gen_courant_1_stop();
    Gen_courant_2_stop();
    resistance_R1 = resistance_1;
    resistance_R2 = resistance_2;
    calculate_current();
    Serial.print("current 1 value is :");
    Serial.println(value_current_1 * 1000000.0);
    Serial.print("current 2 value is :");
    Serial.println(value_current_2 * 1000000.0);
}
float Courant::ohm_law_i(float voltage, uint64_t Resistance)
{
    float Current = 0;
    Current = voltage / (float)Resistance;
    return Current;
}
void Courant::calculate_current()
{
    value_current_1 = ohm_law_i(value_5V, resistance_R1);
    value_current_2 = ohm_law_i(value_5V, resistance_R2);
}

void Courant::Gen_courant_1_start()
{
    digitalWrite(pin_current_1, HIGH);
}

void Courant::Gen_courant_1_stop()
{
    digitalWrite(pin_current_1, LOW);
}

void Courant::Gen_courant_2_start()
{
    digitalWrite(pin_current_2, HIGH);
}

void Courant::Gen_courant_2_stop()
{
    digitalWrite(pin_current_2, LOW);
}

float Courant::get_courant_1()
{
    return value_current_1 * 1000000.0;
}
float Courant::get_courant_2()
{
    return value_current_2 * 1000000.0;
}