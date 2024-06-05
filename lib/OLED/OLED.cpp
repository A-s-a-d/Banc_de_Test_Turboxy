#include "oled.h"
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

// 'logo-horizontal-crop-reduit', 128x64px
const unsigned char epd_bitmap_logo_horizontal_crop_reduit[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x18, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x38, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x39, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x39, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x7b, 0xde, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x73, 0xce, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xf3, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xf7, 0x8f, 0x00, 0x00, 0x18, 0x03, 0x00, 0x0c, 0x01, 0x80, 0x03, 0xfe, 0x00, 0xc0, 0x06,
    0x00, 0xe7, 0x07, 0x00, 0x00, 0x38, 0x03, 0x00, 0x0c, 0x01, 0xc0, 0x03, 0xff, 0x80, 0xe0, 0x06,
    0x01, 0xe7, 0x0f, 0x80, 0x00, 0x3C, 0x03, 0x80, 0x1c, 0x03, 0xc0, 0x03, 0xff, 0xc0, 0x60, 0x0c,
    0x01, 0xcf, 0x7f, 0xe0, 0x00, 0x3C, 0x01, 0x80, 0x18, 0x03, 0xc0, 0x03, 0x01, 0xe0, 0x70, 0x0c,
    0x03, 0xcf, 0xff, 0xf8, 0x00, 0x7c, 0x01, 0x80, 0x18, 0x03, 0xe0, 0x03, 0x00, 0x70, 0x30, 0x18,
    0x03, 0xdf, 0xff, 0xfc, 0x00, 0x6e, 0x01, 0xc0, 0x38, 0x07, 0x60, 0x03, 0x00, 0x30, 0x38, 0x18,
    0x03, 0x9f, 0xf1, 0xfc, 0x00, 0x66, 0x00, 0xc0, 0x30, 0x06, 0x60, 0x03, 0x00, 0x38, 0x18, 0x38,
    0x07, 0x9f, 0xc1, 0xfc, 0x00, 0xc6, 0x00, 0xc0, 0x30, 0x06, 0x70, 0x03, 0x00, 0x18, 0x1c, 0x30,
    0x07, 0x3f, 0x00, 0xec, 0x00, 0xc7, 0x00, 0xe0, 0x70, 0x0e, 0x30, 0x03, 0x00, 0x18, 0x0c, 0x70,
    0x0f, 0x3e, 0x00, 0xe0, 0x00, 0xc3, 0x00, 0x60, 0x60, 0x0c, 0x30, 0x03, 0x00, 0x18, 0x0e, 0x60,
    0x0f, 0x3C, 0x00, 0xf0, 0x01, 0x83, 0x00, 0x60, 0x60, 0x0c, 0x18, 0x03, 0x00, 0x18, 0x06, 0xe0,
    0x0e, 0x78, 0x00, 0x70, 0x01, 0x83, 0x80, 0x70, 0xe0, 0x18, 0x18, 0x03, 0x00, 0x18, 0x07, 0xc0,
    0x1e, 0x78, 0x00, 0x70, 0x01, 0x81, 0x80, 0x30, 0xc0, 0x18, 0x1c, 0x03, 0x00, 0x18, 0x03, 0xc0,
    0x1c, 0xf0, 0x00, 0x38, 0x03, 0x01, 0x80, 0x30, 0xc0, 0x18, 0x0c, 0x03, 0x00, 0x18, 0x03, 0x80,
    0x1c, 0xf0, 0x00, 0x38, 0x03, 0xff, 0xc0, 0x39, 0xc0, 0x3f, 0xfc, 0x03, 0x00, 0x18, 0x01, 0x80,
    0x1c, 0xe0, 0x00, 0x38, 0x03, 0xff, 0xc0, 0x19, 0x80, 0x3f, 0xfe, 0x03, 0x00, 0x18, 0x03, 0x00,
    0x1c, 0xe0, 0x00, 0x38, 0x07, 0xff, 0xc0, 0x19, 0x80, 0x3f, 0xfe, 0x03, 0x00, 0x38, 0x03, 0x00,
    0x1c, 0xc0, 0x00, 0x38, 0x06, 0x00, 0xe0, 0x1f, 0x80, 0x60, 0x06, 0x03, 0x00, 0x70, 0x06, 0x00,
    0x1c, 0x00, 0x00, 0x38, 0x0e, 0x00, 0x60, 0x0f, 0x00, 0x60, 0x07, 0x03, 0x00, 0xf0, 0x06, 0x00,
    0x1c, 0x00, 0x00, 0x38, 0x0c, 0x00, 0x60, 0x0f, 0x00, 0xe0, 0x03, 0x03, 0x03, 0xe0, 0x0c, 0x00,
    0x1c, 0x00, 0x00, 0x38, 0x0c, 0x00, 0x70, 0x0f, 0x00, 0xc0, 0x03, 0x03, 0xff, 0xc0, 0x0c, 0x00,
    0x1e, 0x00, 0x00, 0x78, 0x1c, 0x00, 0x30, 0x06, 0x00, 0xc0, 0x03, 0x83, 0xff, 0x00, 0x18, 0x00,
    0x0e, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0f, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x80, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0xe0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0xf8, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 1040)
const int epd_bitmap_allArray_LEN = 1;
const unsigned char *epd_bitmap_allArray[1] = {
    epd_bitmap_logo_horizontal_crop_reduit};

Oled::Oled() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET), display_2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

void Oled::begin()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, adress_ecran_1))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }
    display.clearDisplay();
    display.display();

    if (!display_2.begin(SSD1306_SWITCHCAPVCC, adress_ecran_2))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }
    display_2.clearDisplay();
    display_2.display();
}

void Oled::logo_s1()
{
    display.clearDisplay();
    display.drawBitmap(0, 0, epd_bitmap_logo_horizontal_crop_reduit, 128, 64, 1);
    display.display();
}

void Oled::logo_s2()
{
    display_2.clearDisplay();
    display_2.drawBitmap(0, 0, epd_bitmap_logo_horizontal_crop_reduit, 128, 64, 1);
    display_2.display();
}

void Oled::temperature(float temperature_turboxy, float temperature_capteur)
{

    display.clearDisplay();
    display.setFont(&FreeMono9pt7b);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    display.print("Temperature");

    display.drawRect(0, 16, SCREEN_WIDTH, SCREEN_HEIGHT - 16, SSD1306_WHITE);

    display.drawLine(SCREEN_WIDTH / 2, 16, SCREEN_WIDTH / 2, SCREEN_HEIGHT, SSD1306_WHITE);

    display.drawLine(0, 28, 128, 28, SSD1306_WHITE);

    display.setFont(NULL);

    display.setCursor(5, 18);
    display.setTextSize(1);
    display.print("Turboxy:");

    display.setCursor(6, 42);
    display.setTextSize(1);
    display.print(temperature_turboxy, 1);
    display.print((char)247); // Degree
    display.print("C");

    display.setCursor(70, 18);
    display.setTextSize(1);
    display.print("Capteur:");

    display.setCursor(70, 42);
    display.setTextSize(1);
    display.print(temperature_capteur, 1);
    display.print((char)247); // Degree
    display.print("C");

    display.display();
}

void Oled::temperature_validation(bool valid)
{
    if (valid == 0)
    {
        display.clearDisplay();
        display.setFont();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 10);
        display.print("Temperature\nerreur");
        display.display();
    }
    else
    {
        display.clearDisplay();
        display.setFont();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 10);
        display.print("Temperature\nOK");
        display.display();
    }
}

void Oled::pressbutton_1()
{
    display.clearDisplay();
    display.setFont();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Press\nButton1");
    display.display();
}

void Oled::Moving_Servo()
{
    display.clearDisplay();
    display.setFont();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Moving\nServo");
    display.display();
}

void Oled::erreur_communicatio_turboxy()
{
    display.clearDisplay();
    display.setFont();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Erreur\ncomm");
    display.display();
}

void Oled::courant_validation(float courant_reference, bool valid)
{
    if (valid == 1)
    {
        display.clearDisplay();
        display.setFont();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 10);
        display.print("courant\n");
        display.print(courant_reference);
        display.print("\nOK");
        display.display();
    }
    else
    {

        display.clearDisplay();
        display.setFont();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 10);
        display.print("courant\n");
        display.print(courant_reference);
        display.print("erreur");
        display.display();
    }
}

void Oled::current(float current_turboxy, float current_generated)
{
    display.clearDisplay();
    display.setFont(&FreeMono9pt7b);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    display.print("COURANT");

    display.drawRect(0, 16, SCREEN_WIDTH, SCREEN_HEIGHT - 16, SSD1306_WHITE);

    display.drawLine(SCREEN_WIDTH / 2, 16, SCREEN_WIDTH / 2, SCREEN_HEIGHT, SSD1306_WHITE);

    display.drawLine(0, 28, 128, 28, SSD1306_WHITE);

    display.setFont(NULL);

    display.setCursor(5, 18);
    display.setTextSize(1);
    display.print("Turboxy:");

    display.setCursor(6, 42);
    display.setTextSize(1);
    display.print(current_turboxy, 1);
    display.print(" A");

    display.setCursor(70, 18);
    display.setTextSize(1);
    display.print("generé:");

    display.setCursor(70, 42);
    display.setTextSize(1);
    display.print(current_generated, 1);
    display.print(" A");

    display.display();
}

void Oled::chlore(float chlore_turboxy, float chlore_generated)
{
    display.clearDisplay();
    display.setFont(&FreeMono9pt7b);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    display.print("Chlore");

    display.drawRect(0, 16, SCREEN_WIDTH, SCREEN_HEIGHT - 16, SSD1306_WHITE);

    display.drawLine(SCREEN_WIDTH / 2, 16, SCREEN_WIDTH / 2, SCREEN_HEIGHT, SSD1306_WHITE);

    display.drawLine(0, 28, 128, 28, SSD1306_WHITE);

    display.setFont(NULL);

    display.setCursor(5, 18);
    display.setTextSize(1);
    display.print("Turboxy:");

    display.setCursor(6, 42);
    display.setTextSize(1);
    display.print(chlore_turboxy, 1);
    display.print(" A");

    display.setCursor(70, 18);
    display.setTextSize(1);
    display.print("generé:");

    display.setCursor(70, 42);
    display.setTextSize(1);
    display.print(chlore_generated, 1);
    display.print(" A");

    display.display();
}

void Oled::pressbutton_2()
{
    display_2.clearDisplay();
    display_2.setFont();
    display_2.setTextSize(3);
    display_2.setTextColor(SSD1306_WHITE);
    display_2.setCursor(0, 0);
    display_2.print("Press\nButton2");
    display_2.display();
}

void Oled::pressure(float pression_depart, float pression_actuelle)
{

    display_2.clearDisplay();
    display_2.setFont(&FreeMono9pt7b);
    display_2.setTextSize(1);
    display_2.setTextColor(SSD1306_WHITE);
    display_2.setCursor(0, 10);
    display_2.print("pression");

    display_2.drawRect(0, 16, SCREEN_WIDTH, SCREEN_HEIGHT - 16, SSD1306_WHITE);

    display_2.drawLine(SCREEN_WIDTH / 2, 16, SCREEN_WIDTH / 2, SCREEN_HEIGHT, SSD1306_WHITE);

    display_2.drawLine(0, 28, 128, 28, SSD1306_WHITE);

    display_2.setFont(NULL);

    display_2.setCursor(5, 18);
    display_2.setTextSize(1);
    display_2.print("Depart:");

    display_2.setCursor(6, 42);
    display_2.setTextSize(1);
    display_2.print(pression_depart, 1);
    display_2.print("mbar");

    display_2.setCursor(70, 18);
    display_2.setTextSize(1);
    display_2.print("Actuelle:");

    display_2.setCursor(65, 42);
    display_2.setTextSize(1);
    display_2.print(pression_actuelle, 1);
    display_2.print("mbar");

    display_2.display();
}

void Oled::fillingair()
{
    display_2.clearDisplay();
    display_2.setFont();
    display_2.setTextSize(3);
    display_2.setTextColor(SSD1306_WHITE);
    display_2.setCursor(0, 0);
    display_2.print("filling\n Air");
    display_2.display();
}

void Oled::testing_frequency(float frequency)
{
    display_2.clearDisplay();
    display_2.setFont();
    display_2.setTextSize(2);
    display_2.setTextColor(SSD1306_WHITE);
    display_2.setCursor(0, 0);
    display_2.print("Freq\n");
    display_2.print(frequency);
    display_2.print(" Hz");
    display_2.display();
}

void Oled::pression_validation(float delta, bool valid)
{
    display_2.clearDisplay();
    display_2.setFont();
    display_2.setTextSize(2);
    display_2.setTextColor(SSD1306_WHITE);
    display_2.setCursor(0, 0);
    display_2.print("delta:\n");
    display_2.print(delta, 2);
    display_2.print("mBar");

    if (valid == 1)
    {
        display_2.setCursor(0, 40);
        display_2.print("Valid");
    }
    else
    {
        display_2.setCursor(0, 40);
        display_2.print("non Valid");
    }

    display_2.display();
}

void Oled::frequency_validation(uint8_t frequency, bool valid)
{
    display_2.clearDisplay();
    display_2.setFont();
    display_2.setTextSize(2);
    display_2.setTextColor(SSD1306_WHITE);
    display_2.setCursor(0, 0);
    display_2.print("freq:\n");
    display_2.print(frequency);
    display_2.print(" HZ");

    if (valid == 1)
    {
        display_2.setCursor(0, 40);
        display_2.print(" OK");
    }
    else
    {
        display_2.setCursor(0, 40);
        display_2.print(" xxx");
    }

    display_2.display();
}

void Oled::affichage_resultats(bool valid_temp, bool valid_courant1, bool valid_courant2)
{

    display.clearDisplay();
    display.setFont(&FreeSans9pt7b);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 12);

    if (valid_temp == 1)
    {
        display.print("Temp");
        display.print((char)247);
        display.print("OK");
    }
    else
    {
        display.print("Temp xx");
    }

    if (valid_courant1 == 1)
    {
        display.print("\nCourant1 OK");
    }
    else
    {
        display.print("\nCourant1 XX");
    }

    if (valid_courant2 == 1)
    {
        display.print("\nCourant2 OK");
    }
    else
    {
        display.print("\nCourant2 XX");
    }
    display.display();
    display.setFont();
}