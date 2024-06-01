
#include "main.h"

Capteur_de_temperature cap_temp;
START_BUTTON startButton;
Turboxy turboxy;
Courant Gen_courant;
Servo_rack servo_sonde;
BUTTON_PRESSION B_Pression;
valve Electrovanne;
A10_Pressure_Sensor Pressure_Sensor;
Oled display;

// ++++++++++++++++++++++++++++++++++ SETUP +++++++++++++++++++++++++++++++++++++
void setup()
{

  WIRE.begin();
  Serial.begin(9600);
  // while (!Serial)
  //   delay(10);

  begin_ADC();
  startButton.begin_button_interruption();
  B_Pression.begin_interruption();
  Gen_courant.begin(390000, 25500);
  servo_sonde.begin();
  Electrovanne.begin();
  Serial.println("Setup"); // affichage pour dire que setup a bien ete executé
  start_test = 100;
  Serial.println(turboxy.begin());

  display.begin();
  delay(100);
  display.logo();
  delay(1000);
}

// ++++++++++++++++++++++++++++++++++ LOOP  +++++++++++++++++++++++++++++++++++++
void loop()
{
  bool do_ = 1;
  while (do_ == 1)
  {

    switch (etape_test_I_T) // cycle teste
    {
    case 0:
    {
      display.pressbutton_1();
      servo_sonde.move_in_place(servo_position_repos);
      Gen_courant.Gen_courant_2_stop();
      Gen_courant.Gen_courant_1_stop();
      static uint32_t nextTime0 = 0;
      if (millis() - nextTime0 >= interval_wait_message_press_button)
      {
        nextTime0 += interval_wait_message_press_button;
        Serial.println("waiting for test to start");
      }
      if (start_test == 1)
      {
        etape_test_I_T = 1;
      }
      else
      {
        etape_test_I_T = 0;
      }
      start_test = 0;
    }
    break;
    case 1:
    {
      display.Moving_Servo();
      Serial.println("moving servo");
      servo_sonde.move_in_place(servo_position_test);

      etape_test_I_T = 2;
    }
    break;
    case 2:
    {
      static uint8_t test_temp_count = 0;
      static uint32_t nextTime1 = 0;
      // Check if the delay passed
      if (millis() - nextTime1 >= interval_wait_get_temperature)
      {
        nextTime1 = millis(); // Update the next time to the current time
        float Temperature_Reference_test = cap_temp.GetTemperature();

        float Temperature_Turboxy = turboxy.GET_TEMPERATURE();
        if (Temperature_Turboxy >= 0) //-1 = error communication
        {
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
          test_temp_count++;
        }
        display.temperature(Temperature_Turboxy, Temperature_Reference_test);
      }

      if (test_temp_count >= 5)
      {
        etape_test_I_T = 3;
        test_temp_count = 0;
      }
    }
    break;
    case 3:
    {
      static uint8_t test_current1_count = 0;
      Gen_courant.Gen_courant_2_stop();
      static uint32_t nextTime2 = 0;
      if (millis() - nextTime2 >= interval_wait_current)
      {
        nextTime2 = millis(); // Update nextTime2 to the current time
        Serial.println("\ntesting current 1");
        Gen_courant.Gen_courant_1_start();
        float Courant_Reference_test = Gen_courant.get_courant_1();
        float Courant_Turboxy = turboxy.GET_CHLORE();
        display.current(Courant_Turboxy, Courant_Reference_test);

        if (Courant_Turboxy >= 0) //-1 = error communication
        {
          Serial.print("le courant de Turboxy est ");
          Serial.print(Courant_Turboxy, 5);
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
          test_current1_count++;
        }
      }
      if (test_current1_count >= nbr_de_mesures_courant)
      {
        etape_test_I_T = 4;
        test_current1_count = 0;
        Gen_courant.Gen_courant_2_stop();
      }
      Gen_courant.Gen_courant_2_stop();
    }
    break;
    case 4:
    {
      static uint8_t test_current2_count = 0;
      Gen_courant.Gen_courant_1_stop();

      static uint32_t nextTime3 = 0;
      if (millis() - nextTime3 >= interval_wait_current)
      {
        nextTime3 = millis();
        Serial.println("\ntesting current 2");
        Gen_courant.Gen_courant_2_start();
        float Courant_Reference_test = Gen_courant.get_courant_2();
        float Courant_Turboxy = turboxy.GET_CHLORE();
        display.current(Courant_Turboxy, Courant_Reference_test);
        if (Courant_Turboxy >= 0) // -1 = error communication
        {
          Serial.print("le courant de Turboxy est ");
          Serial.print(Courant_Turboxy, 5);
          Serial.print(" et celle generé est ");
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
          test_current2_count++; // Increment count
        }
      }
      if (test_current2_count >= nbr_de_mesures_courant)
      {
        etape_test_I_T = 0xFF;
        test_current2_count = 0;
      }
      Gen_courant.Gen_courant_1_stop();
    }
    break;

    case 0xFF:
    {
      Gen_courant.Gen_courant_1_stop();
      Gen_courant.Gen_courant_2_stop();
      servo_sonde.move_in_place(servo_position_repos);
      etape_test_I_T = 0;
    }
    break;
    default:
    {
    }
    break;
    }

    switch (etape_test_flux)
    {
    case 0:
    {
      Electrovanne.IN_OFF();
      Electrovanne.OUT_OFF();
      static uint32_t nextTime0_0 = 0;

      if (millis() - nextTime0_0 >= interval_wait_message_pressure_button)
      {
        nextTime0_0 = millis();
        Serial.println("waiting for pressure button to start");
      }
      if (start_pression == 1)
      {
        etape_test_flux = 1;
      }
      else
      {
        etape_test_flux = 0;
      }
      start_pression = 0;
    }
    break;
    case 1:
    {
      static uint32_t nextTime0_1 = 0;
      if (millis() - nextTime0_1 >= interval_wait_pressure_increase)
      {
        nextTime0_1 = millis();
      }

      Serial.println("filling the Air");
      Electrovanne.IN_ON();
      Electrovanne.OUT_OFF();
      etape_test_flux = 2;
    }
    break;
    case 2:
    {
      static uint32_t nextTime0_2 = 0;
      if (millis() - nextTime0_2 >= interval_wait_positioning_valves)
      {
      }

      nextTime0_2 = millis();
      Serial.println("start testing pressure");

      Electrovanne.IN_OFF();
      Electrovanne.OUT_OFF();
      etape_test_flux = 3;
    }
    break;
    case 3:
    {
      static float Pressure = 0;
      static uint8_t pressure_mesure_count = 0;
      Electrovanne.IN_OFF();
      Electrovanne.OUT_OFF();

      static uint32_t nextTime0_3 = 0;
      if (millis() - nextTime0_3 >= interval_wait_pressure)
      {
        nextTime0_3 = millis();
        Serial.println("testing pressure");
        Pressure = Pressure_Sensor.get_pressure_Bar();
        Serial.print("La pression est: ");
        Serial.print(Pressure);
        Serial.println(" mBar");
        pressure_mesure_count++;
      }
      if (pressure_mesure_count >= 5)
      {
        etape_test_flux = 4;
        pressure_mesure_count = 0;
      }
    }
    break;

    default:
      etape_test_flux = 0;
      break;
    }
  }
}
