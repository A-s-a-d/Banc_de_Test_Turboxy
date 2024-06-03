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
#define adress_ecran_1 0x3C
#define adress_ecran_2 0x3D


class Oled
{
public:
    Oled();
    void begin();
    void logo_s1();
    void logo_s2();
    void temperature(float temperature_turboxy, float tmperature_capteur);
    void pressbutton_1();
    void pressbutton_2();
    void pressure(float pression_depart, float pression_actuelle);
    void Moving_Servo();
    void current(float current_turboxy, float current_generated);
private:
    Adafruit_SSD1306 display;
    Adafruit_SSD1306 display_2;
};


#endif