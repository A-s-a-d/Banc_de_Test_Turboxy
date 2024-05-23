#ifndef __START_BUTTON__H__
#define __START_BUTTON__H__

#include <Arduino.h>
#define start_button_pin 2

extern volatile uint8_t start_test;

class START_BUTTON
{
private:
    /* data */
public:
    START_BUTTON(/* args */);
    void begin_button_interruption();

    static void start_press_button();
};

#endif