#include "START_BUTTON.h"

volatile uint8_t start_test = 0;

START_BUTTON::START_BUTTON()
{
}

void START_BUTTON::begin_button_interruption()
{
    pinMode(start_button_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(start_button_pin), start_press_button, FALLING);
}

void START_BUTTON::start_press_button()
{
    if (start_test == 0)
    {
        start_test = 1;
    }
}
