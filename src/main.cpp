
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
  display.logo_s1();
  display.logo_s2();
  delay(1000);
}

// ++++++++++++++++++++++++++++++++++ LOOP  +++++++++++++++++++++++++++++++++++++
void loop()
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
    static bool valid = 0;
    static uint8_t nbr_valid = 0;
    static uint32_t nexttime_display = 0;
    static uint32_t seconds_since_display = 0;

    // Check if the delay passed
    if (test_temp_count < 5)
    {
      if (millis() - nextTime1 >= interval_wait_get_temperature)
      {
        nextTime1 = millis(); // Update the next time to the current time
        float Temperature_Reference_test = cap_temp.GetTemperature();

        float Temperature_Turboxy = turboxy.GET_TEMPERATURE();
        if (Temperature_Turboxy >= 0) // -1 = error communication
        {
          Serial.print("la temperature de Turboxy est ");
          Serial.print(Temperature_Turboxy);
          cap_temp.display_temp_Serial();

          // Check the temperature difference
          if (Temperature_Turboxy > Temperature_Reference_test + 3.0 || Temperature_Turboxy < Temperature_Reference_test - 3.0)
          {
            Test_Temperature_Valid = 0;
            Serial.println("test temperature non Valid");
          }
          else
          {
            Test_Temperature_Valid = 1;
            Serial.println("****************test temperature Valid");
            nbr_valid++;
          }
          test_temp_count++;
        }
        else
        {
          problem_com_turboxy = 1;
          test_temp_count++;
        }
        display.temperature(Temperature_Turboxy, Temperature_Reference_test);
      }
    }
    else
    {
      if (nbr_valid < 4)
      {
        valid = 0;
      }
      else
      {
        valid = 1;
      }

      const uint16_t display_time = 1000;

      if ((millis() - nexttime_display >= display_time) * (seconds_since_display < 5))
      {
        nexttime_display = millis(); // Update the next time to the current time
        display.temperature_validation(valid);
        seconds_since_display++;
      }
      else if (seconds_since_display >= 5)
      {
        etape_test_I_T = 3;
        test_temp_count = 0;
        seconds_since_display = 0;
        nbr_valid = 0;
        valid = 0;
      }
    }

    if (problem_com_turboxy == 1)
    {
      etape_test_I_T = 0xEE;
      problem_com_turboxy = 0;
    }
  }

  break;
  case 3:
  {
    static float somme_moyenne_courant_1 = 0;
    static uint8_t test_current1_count = 0;
    static uint32_t nextTime2 = 0;
    static uint8_t problem_com_turboxy = 0;

    Gen_courant.Gen_courant_2_stop();

    if (test_current1_count >= nbr_de_mesures_courant)
    {
      etape_test_I_T = 31;
      test_current1_count = 0;
      somme_moyenne_courant_1 = 0; // Reset sum for next round of tests
      Gen_courant.Gen_courant_2_stop();

      float moyenne_courant = somme_moyenne_courant_1 / nbr_de_mesures_courant;
      if (moyenne_courant > Courant1_Reference_test + 5 || moyenne_courant < Courant1_Reference_test - 5)
      {
        validation_courant_1_finale = 0;
      }
      else
      {
        validation_courant_1_finale = 1;
      }
    }
    else if (millis() - nextTime2 >= interval_wait_current)
    {
      nextTime2 = millis(); // Update nextTime2 to the current time
      Serial.println("\ntesting current 1");
      Gen_courant.Gen_courant_1_start();
      Courant1_Reference_test = Gen_courant.get_courant_1();

      /* * */
      Courant1_Reference_test = 76.7; // a modifier apres aec la vrai valeur
      /* * */

      float Chlore_Turboxy = turboxy.GET_CHLORE() / 100;
      display.current(Chlore_Turboxy, Courant1_Reference_test);

      if (Chlore_Turboxy >= 0) // -1 = error communication
      {
        Serial.print("le courant de Turboxy est ");
        Serial.print(Chlore_Turboxy, 5);
        Serial.print(" et celle generé est ");
        Serial.println(Courant1_Reference_test);
        if (Chlore_Turboxy > Courant1_Reference_test + 5 || Chlore_Turboxy < Courant1_Reference_test - 5) // 3 c'est l'erreur accepté ici
        {
          Test_courant1_Valid = 0;
          Serial.println("test courant 1 non Valid");
        }
        else
        {
          Test_courant1_Valid = 1;
          Serial.println("****************test courant 1 Valid");
        }
        somme_moyenne_courant_1 += Chlore_Turboxy;
        test_current1_count++;
      }
      else
      {
        problem_com_turboxy = 1;
      }
    }

    if (problem_com_turboxy == 1)
    {
      etape_test_I_T = 0xEE;
    }

    Gen_courant.Gen_courant_2_stop();
  }
  break;

  case 31:
  {
    static uint32_t nextTime31 = 0;
    static uint8_t time_count = 0;

    if (millis() - nextTime31 >= interval_display)
    {
      nextTime31 = millis();
      Serial.println("waiting for test to start");
      display.courant_validation(Courant1_Reference_test, validation_courant_1_finale);
      time_count++;
    }

    if (time_count >= 5)
    {
      etape_test_I_T = 4;
      time_count = 0; // Reset time_count for the next round
    }
  }
  break;

  case 4:
  {
    static float somme_moyenne_courant_2 = 0;
    static uint8_t test_current2_count = 0;
    Gen_courant.Gen_courant_1_stop();
    static uint32_t nextTime3 = 0;
    float Courant2_Reference_test = 0;

    if (test_current2_count >= nbr_de_mesures_courant)
    {
      if (somme_moyenne_courant_2 / nbr_de_mesures_courant > Courant2_Reference_test + 5 || somme_moyenne_courant_2 / nbr_de_mesures_courant < Courant2_Reference_test - 5)
      {
        validation_courant_2_finale = 0;
      }
      else
      {
        validation_courant_2_finale = 1;
      }
      etape_test_I_T = 0x41;
      test_current2_count = 0;
      somme_moyenne_courant_2 = 0;
    }
    else if (millis() - nextTime3 >= interval_wait_current)
    {
      nextTime3 = millis();
      Serial.println("\ntesting current 2");
      Gen_courant.Gen_courant_2_start();
      Courant2_Reference_test = Gen_courant.get_courant_2();
      float Courant_Turboxy = turboxy.GET_CHLORE() / 100;

      /* * */

      Courant2_Reference_test = 220; // a modifier apres aec la vrai valeur

      /* * */

      display.current(Courant_Turboxy, Courant2_Reference_test);

      if (Courant_Turboxy >= 0) // -1 = error communication
      {
        Serial.print("le courant de Turboxy est ");
        Serial.print(Courant_Turboxy, 5);
        Serial.print(" et celle generé est ");
        Serial.println(Courant2_Reference_test);
        if (Courant_Turboxy > Courant2_Reference_test + 5 || Courant_Turboxy < Courant2_Reference_test - 5)
        {
          Test_courant2_Valid = 0;
          Serial.println("test courant 2 non Valid");
        }
        else
        {
          Test_courant2_Valid = 1;
          Serial.println("****************test courant 2 Valid");
        }
        somme_moyenne_courant_2 += Courant_Turboxy;

        test_current2_count++; // Increment count
      }
      else
      {
        problem_com_turboxy = 1;
      }
    }

    if (problem_com_turboxy == 1)
    {
      etape_test_I_T = 0xEE;
    }

    Gen_courant.Gen_courant_1_stop();
  }
  break;

  case 0x41:
  {
    static uint32_t nextTime41 = 0;
    static uint8_t time_count = 0;
    if (millis() - nextTime41 >= interval_display)
    {
      nextTime41 += millis();
      Serial.println("waiting for test to start");
      display.courant_validation(Courant2_Reference_test, validation_courant_2_finale);
      time_count++;
    }

    if (time_count >= 5)
    {
      etape_test_I_T = 0xFF;
    }
  }
  break;

  case 0xFF:
  {
    Gen_courant.Gen_courant_1_stop();
    Gen_courant.Gen_courant_2_stop();
    servo_sonde.move_in_place(servo_position_repos);
    etape_test_I_T = 0;
    problem_com_turboxy = 0;
  }
  break;

  case 0xEE: // erreur de communication
  {

    display.erreur_communicatio_turboxy();
    problem_com_turboxy = 0;
    if (start_test == 1)
    {
      etape_test_I_T = 0;
    }
    else
    {
      etape_test_I_T = 0xEE;
    }
    start_test = 0;
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
    display.pressbutton_2();
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
      nextTime0_2 = millis();
    }

    Serial.println("start testing pressure");
    Electrovanne.IN_OFF();
    Electrovanne.OUT_OFF();
    delay(1);
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
      display.pressure(2.0, Pressure / 1000.0);
      Serial.print("La pression est: ");
      Serial.print(Pressure);
      Serial.println(" mBar");
      pressure_mesure_count++;
    }
    if (pressure_mesure_count >= 10)
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
