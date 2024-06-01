#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

class Oled
{
public:
    Oled();
    void begin();
    void logo();
    void temperature(float temperature_turboxy, float tmperature_capteur);
    void pressbutton_1();
    void Moving_Servo();
    void current(float current_turboxy, float current_generated);
private:
    Adafruit_SSD1306 display;
};

#endif