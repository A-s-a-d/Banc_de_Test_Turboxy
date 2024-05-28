#include "Button_pression.h"

volatile uint8_t start_pression = 0;

BUTTON_PRESSION::BUTTON_PRESSION()
{
}

void BUTTON_PRESSION::begin_interruption()
{
    pinMode(pression_button_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(pression_button_pin), press, FALLING);
}

void BUTTON_PRESSION::press()
{
    if (start_pression == 0)
    {
        start_pression = 1;
    }
}
