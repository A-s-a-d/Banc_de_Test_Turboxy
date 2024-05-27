
#include "main.h"

Capteur_de_temperature cap_temp;
START_BUTTON startButton;
Turboxy turboxy;

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
    for (uint8_t i = 0; i < 5;)
    {
      static uint32_t nextTime;
      if (millis() - nextTime >= interval_wait_get_temperature)
      {
        nextTime += interval_wait_get_temperature;
        float Temperature_Reference_test = cap_temp.GetTemperature();
        float Temperature_Turboxy = turboxy.GET_TEMPERATURE();
        Serial.print("la temperature de Turboxy est");
        Serial.print(Temperature_Turboxy);
        Serial.print("et celle de Capteur de temperature est");
        Serial.print(Temperature_Reference_test);
        if (Temperature_Turboxy > Temperature_Reference_test + 2.0 || Temperature_Turboxy < Temperature_Reference_test - 2.0)
        {
          Test_Temperature_Valid = 0;
          Serial.println("test temperature non Valid");
        }
        else
        {
          Test_Temperature_Valid = 1;
          Serial.println("****************test temperature Valid");
        }
        i++;
      }
    }
    etape = 2;
  }
  break;
  case 2:
  {
    etape = 3;
  }
  break;
  case 3:
  {
    etape = 0;
  }
  break;
  default:
    break;
  }
}
