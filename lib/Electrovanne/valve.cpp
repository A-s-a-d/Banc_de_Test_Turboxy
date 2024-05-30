#include "valve.h"

valve::valve(/* args */)
{
}

void valve::begin()
{
    pinMode(Pin_Elecreovanne_IN, OUTPUT);
    pinMode(Pin_Electrovanne_OUT, OUTPUT);
    IN_OFF();
    OUT_OFF();
}

void valve::IN_ON()
{
    digitalWrite(Pin_Elecreovanne_IN, ON);
}
void valve::IN_OFF()
{
    digitalWrite(Pin_Elecreovanne_IN, OFF);
}
void valve::OUT_ON()
{
    digitalWrite(Pin_Electrovanne_OUT, ON);
}
void valve::OUT_OFF()
{
    digitalWrite(Pin_Electrovanne_OUT, OFF);
}