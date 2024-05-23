
#include "main.h"

Capteur_de_temperature cap_temp;
START_BUTTON startButton;

// ++++++++++++++++++++++++++++++++++ SETUP +++++++++++++++++++++++++++++++++++++
void setup()
{
  WIRE.begin();
  Serial.begin(9600);
  while (!Serial)
    delay(10);
  begin_ADC();
  startButton.begin_button_interruption();
  Serial.println("Setup"); // affichage pour dire que setup a bien ete executé
  start_test = 100;
}

// ++++++++++++++++++++++++++++++++++ LOOP  +++++++++++++++++++++++++++++++++++++
void loop()
{
  switch (etape) // cycle teste
  {
  case 0:
  {
    static uint32_t nextTime;
    if (millis() - nextTime >= interval_wait_message_press_button)
    {
      nextTime += interval_wait_message_press_button;
      Serial.println("waiting for test to start");
    }
    if (start_test == 1)
    {
      etape = 1;
    }
    else
    {
      etape = 0;
    }
    start_test = 0;
  }
  break;

  case 1:
  {
    static uint32_t nextTime;
    if (millis() - nextTime >= interval_wait_get_temperature)
    {
      nextTime += interval_wait_get_temperature;
      float Temperature_Reference_test = cap_temp.GetTemperature();

      if (DATA_TEMPERATURE_RECIVED_TURBOXY > Temperature_Reference_test + 2.0 || DATA_TEMPERATURE_RECIVED_TURBOXY < Temperature_Reference_test - 2.0)
      {
        Test_Temperature_Valid = 0;
        Serial.println("test temperature non Valid");
      }
      else
      {
        Test_Temperature_Valid = 1;
        Serial.println("****************test temperature Valid");
      }
      etape = 2;
    }
  }
  break;
  case 2:
  {
    etape = 3;
  }
  break;

  case 3:
    etape = 0;
    break;

  default:
    break;
  }
}
