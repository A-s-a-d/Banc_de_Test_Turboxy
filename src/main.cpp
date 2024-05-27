
#include "main.h"

Capteur_de_temperature cap_temp;
START_BUTTON startButton;
Turboxy turboxy;
Courant Gen_courant;

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
  Gen_courant.begin(390000, 25500);
}

// ++++++++++++++++++++++++++++++++++ LOOP  +++++++++++++++++++++++++++++++++++++
void loop()
{
  switch (etape) // cycle teste
  {
  case 0:
  {

    static uint32_t nextTime0 = 0;
    ;
    if (millis() - nextTime0 >= interval_wait_message_press_button)
    {
      nextTime0 += interval_wait_message_press_button;
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
      static uint32_t nextTime1 = 0;

      // Check if the delay passed
      if (millis() - nextTime1 >= interval_wait_get_temperature)
      {
        nextTime1 = millis(); // Update the next time to the current time
        float Temperature_Reference_test = cap_temp.GetTemperature();
        float Temperature_Turboxy = turboxy.GET_TEMPERATURE();

        Serial.print("la temperature de Turboxy est ");
        Serial.print(Temperature_Turboxy);
        cap_temp.display_temp_Serial();

        // Check the temperature difference
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

        //
        i++;
      }
    }
    etape = 2;
  }
  break;
  case 2:
  {
    Gen_courant.Gen_courant_2_stop();
    Gen_courant.Gen_courant_1_stop();

    for (uint8_t i = 0; i < 5;)
    {
      static uint32_t nextTime2 = 0;

      if (millis() - nextTime2 >= interval_wait_current)
      {
        nextTime2 = millis(); // Update nextTime2 to the current time
        Serial.println("\ntesting current 1");
        Gen_courant.Gen_courant_1_start();
        float Courant_Reference_test = Gen_courant.get_courant_1();
        float Courant_Turboxy = turboxy.GET_CHLORE();

        Serial.print("le courant de Turboxy est ");
        Serial.print(Courant_Turboxy);
        Serial.print("et celle generé est ");
        Serial.println(Courant_Reference_test);

        if (Courant_Turboxy > Courant_Reference_test + 20.0 || Courant_Turboxy < Courant_Reference_test - 20.0)
        {
          Test_courant1_Valid = 0;
          Serial.println("test courant 1 non Valid");
        }
        else
        {
          Test_courant1_Valid = 1;
          Serial.println("****************test courant 1 Valid");
        }

        i++;
      }
    }

    Gen_courant.Gen_courant_2_stop();
    Gen_courant.Gen_courant_1_stop();
    etape = 3;
  }
  break;

  case 3:
  {
    Gen_courant.Gen_courant_1_stop();
    Gen_courant.Gen_courant_2_stop();

    for (uint8_t i = 0; i < 5;)
    {

      static uint32_t nextTime3 = 0;
      ;
      if (millis() - nextTime3 >= interval_wait_current)
      {
        nextTime3 = millis();
        Serial.println("\ntesting current 2");
        Gen_courant.Gen_courant_2_start();
        float Courant_Reference_test = Gen_courant.get_courant_2();
        float Courant_Turboxy = turboxy.GET_CHLORE();

        Serial.print("le courant de Turboxy est ");
        Serial.print(Courant_Turboxy);
        Serial.print("et celle generé est ");
        Serial.println(Courant_Reference_test);

        if (Courant_Turboxy > Courant_Reference_test + 20.0 || Courant_Turboxy < Courant_Reference_test - 20.0)
        {
          Test_courant2_Valid = 0;
          Serial.println("test courant 2 non Valid");
        }
        else
        {
          Test_courant2_Valid = 1;
          Serial.println("****************test courant 2 Valid");
        }
        i++;
      }
    }

    Gen_courant.Gen_courant_1_stop();
    Gen_courant.Gen_courant_2_stop();
    etape = 0;
  }
  break;
  default:
    break;
  }
}
