#ifndef BUTTON_PRESSION_H
#define BUTTON_PRESSION_H

#include <Arduino.h>

#define pression_button_pin 3

extern volatile uint8_t start_pression;

class BUTTON_PRESSION
{
private:
    /* data */
public:
    BUTTON_PRESSION(/* args */);
    void begin_interruption();

    static void press();
};

#endif