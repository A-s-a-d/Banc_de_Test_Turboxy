
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
    static unsigned long nextTime0 = 0;
    if (millis() - nextTime0 >= interval_wait_message_press_button)
    {
      nextTime0 = millis();
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

    courant1.Courant1_Reference_test = 0;
    courant1.moyenne = 0;
    courant1.validation_courant_1_finale = 0;

    courant2.Courant2_Reference_test = 0;
    courant2.moyenne = 0;
    courant2.validation_courant_2_finale = 0;

    temperature.nbr_valid = 0;
    temperature.valid = 0;
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
    static unsigned long nextTime1 = 0;

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
          if (abs(Temperature_Turboxy - Temperature_Reference_test) > 4.0)
          {
            Test_Temperature_Valid = 0;
            Serial.println("test temperature non Valid");
          }
          else
          {
            Test_Temperature_Valid = 1;
            Serial.println("****************test temperature Valid");
            temperature.nbr_valid++;
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
      temperature.valid = (temperature.nbr_valid >= 4);
      etape_test_I_T = 21;
      test_temp_count = 0; // reset variable for next  test
    }

    if (problem_com_turboxy == 1)
    {
      etape_test_I_T = 0xEE;
      problem_com_turboxy = 0;
    }
  }
  break;

  case 21:
  {
    static unsigned long nexttime_display = 0;
    static uint8_t seconds_since_display = 0;

    if (millis() - nexttime_display >= interval_display)
    {
      nexttime_display = millis();
      display.temperature_validation(temperature.valid);
      seconds_since_display++;
    }

    if (seconds_since_display >= 5)
    {
      etape_test_I_T = 3;
      seconds_since_display = 0;
    }
  }
  break;

  case 3:
  {
    static float somme_moyenne_courant_1 = 0;
    static uint8_t test_current1_count = 0;
    static unsigned long nextTime2 = 0;

    Gen_courant.Gen_courant_2_stop();

    if (test_current1_count >= nbr_de_mesures_courant)
    {

      for (uint8_t i = 2; i <= courant1.nbr_values; i++)
      {
        somme_moyenne_courant_1 += courant1.tableval[i];
      }
      courant1.moyenne = somme_moyenne_courant_1 / (courant1.nbr_values - 2);

      if (abs(courant1.moyenne - courant1.Courant1_Reference_test) > tolerence_courant)
      {
        courant1.validation_courant_1_finale = 0;
      }
      else
      {
        courant1.validation_courant_1_finale = 1;
      }

      etape_test_I_T = 31;
      somme_moyenne_courant_1 = 0;
      test_current1_count = 0;

      Gen_courant.Gen_courant_2_stop();
    }
    else if (millis() - nextTime2 >= interval_wait_current)
    {
      nextTime2 = millis(); // Update nextTime2 to the current time
      Serial.println("\ntesting current 1");
      Gen_courant.Gen_courant_1_start();
      courant1.Courant1_Reference_test = Gen_courant.get_courant_1();
      /* * */
      courant1.Courant1_Reference_test = 76.7; // a modifier apres aec la vrai valeur
      /* * */
      float Chlore_Turboxy = turboxy.GET_CHLORE() / 100;
      display.current(Chlore_Turboxy, courant1.Courant1_Reference_test);

      if (Chlore_Turboxy >= 0) // -1 = error communication
      {
        courant1.tableval[test_current1_count] = Chlore_Turboxy;

        Serial.print("le courant de Turboxy est ");
        Serial.print(Chlore_Turboxy, 5);
        Serial.print(" et celle generé est ");
        Serial.println(courant1.Courant1_Reference_test);

        // 5 is the acceptable error here
        if (abs(Chlore_Turboxy - courant1.Courant1_Reference_test) > tolerence_courant)
        {
          courant1.Test_courant1_Valid = 0;
          Serial.println("test courant 1 non Valid");
        }
        else
        {
          courant1.Test_courant1_Valid = 1;
          Serial.println("****************test courant 1 Valid");
        }

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
    static unsigned long nextTime31 = 0;
    static uint8_t time_count = 0;

    if (millis() - nextTime31 >= interval_display)
    {
      nextTime31 = millis();
      Serial.println("waiting for test to start");
      display.courant_validation(courant1.moyenne, courant1.validation_courant_1_finale);
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

    static uint8_t test_current2_count = 0;
    static unsigned long nextTime3 = 0;

    Gen_courant.Gen_courant_1_stop();

    if (test_current2_count >= nbr_de_mesures_courant)
    {
      Serial.println("+++++++++++++++++++++++++++++++++++++++++");
      for (uint8_t i = 2; i <= courant2.nbr_values; i++)
      {
        courant2.somme_moyenne_courant_2 += courant2.tableval[i];
        Serial.println(courant2.somme_moyenne_courant_2);
      }
      courant2.moyenne = courant2.somme_moyenne_courant_2 / (courant2.nbr_values - 2);

      Serial.println(courant2.moyenne, 5);

      if (abs(courant2.moyenne - courant2.Courant2_Reference_test) > tolerence_courant + 5)
      {
        courant2.validation_courant_2_finale = 0;
      }
      else
      {
        courant2.validation_courant_2_finale = 1;
      }
      etape_test_I_T = 0x41;
      test_current2_count = 0;
      courant2.somme_moyenne_courant_2 = 0;
    }
    else if (millis() - nextTime3 >= interval_wait_current)
    {
      nextTime3 = millis();
      Serial.println("\ntesting current 2");
      Gen_courant.Gen_courant_2_start();
      courant2.Courant2_Reference_test = Gen_courant.get_courant_2();
      /* * */
      courant2.Courant2_Reference_test = 220; // a modifier apres aec la vrai valeur
      /* * */
      float Courant_Turboxy = turboxy.GET_CHLORE() / 100;

      display.current(Courant_Turboxy, courant2.Courant2_Reference_test);

      if (Courant_Turboxy >= 0) // -1 = error communication
      {
        courant2.tableval[test_current2_count] = Courant_Turboxy;
        test_current2_count++; // Increment count

        Serial.print("le courant de Turboxy est ");
        Serial.print(Courant_Turboxy, 5);
        Serial.print(" et celle generé est ");
        Serial.println(courant2.Courant2_Reference_test);
        if (abs(Courant_Turboxy - courant2.Courant2_Reference_test) > tolerence_courant)
        {
          courant2.Test_courant2_Valid = 0;
          Serial.println("test courant 2 non Valid");
        }
        else
        {
          courant2.Test_courant2_Valid = 1;
          Serial.println("****************test courant 2 Valid");
        }
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
    static unsigned long nextTime41 = 0;
    static uint8_t time_count = 0;
    if (millis() - nextTime41 >= interval_display)
    {
      nextTime41 = millis();
      Serial.println("waiting for test to start");
      display.courant_validation(courant2.moyenne, courant2.validation_courant_2_finale);
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
    etape_test_I_T = 111;
    problem_com_turboxy = 0;
  }
  break;
  case 111:
  {
    static unsigned long nexttime_display = 0;
    static uint8_t seconds_since_display = 0;

    if (millis() - nexttime_display >= interval_display)
    {
      nexttime_display = millis();
      display.affichage_resultats(temperature.valid, courant1.validation_courant_1_finale, courant2.validation_courant_2_finale);
      seconds_since_display++;
    }

    if (seconds_since_display >= 10)
    {
      etape_test_I_T = 0;
      seconds_since_display = 0;
    }
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
    delay(4000); // a enlever
    Electrovanne.OUT_OFF();
    static unsigned long nextTime0_0 = 0;

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
    static uint8_t pressure_wait_count = 0;
    static unsigned long nextTime0_1 = 0;
    if (millis() - nextTime0_1 >= interval_wait_pressure_increase)
    {
      nextTime0_1 = millis();
      display.fillingair();
      Serial.println("filling the Air");
      Electrovanne.IN_ON();
      Electrovanne.OUT_OFF();
      pressure_wait_count++;
    }
    if (pressure_wait_count >= 3)
    {
      etape_test_flux = 2;
      pressure_wait_count = 0;
    }
  }
  break;

  case 2:
  {
    static unsigned long nextTime0_2 = 0;
    if (millis() - nextTime0_2 >= interval_wait_positioning_valves)
    {
      nextTime0_2 = millis();
    }

    Serial.println("start testing pressure");
    Electrovanne.IN_OFF();
    Electrovanne.OUT_OFF();

    etape_test_flux = 3;
    pressure_delta.pressure_start = Pressure_Sensor.get_pressure_mBar();
  }
  break;
  case 3:
  {

    static float Pressure = 0;
    static uint8_t pressure_mesure_count = 0;
    Electrovanne.IN_OFF();
    Electrovanne.OUT_OFF();

    static unsigned long nextTime0_3 = 0;
    if (millis() - nextTime0_3 >= interval_wait_pressure)
    {
      nextTime0_3 = millis();
      Serial.println("testing pressure");
      Pressure = Pressure_Sensor.get_pressure_mBar();
      display.pressure(pressure_delta.pressure_start, Pressure);
      Serial.print("La pression est: ");
      Serial.print(Pressure);
      Serial.println(" mBar");
      pressure_mesure_count++;
    }

    if (pressure_mesure_count >= nbr_of_pressur_test)
    {
      etape_test_flux = 31;
      pressure_mesure_count = 0;
      pressure_delta.pressure_end = Pressure_Sensor.get_pressure_mBar();

      pressure_delta.delta = pressure_delta.pressure_start - pressure_delta.pressure_end;
      Serial.println("-------------------------------------------");
      Serial.println(pressure_delta.delta);
      if (abs(pressure_delta.delta) <= pressure_delta.erreur_accceptable)
      {

        pressure_delta.pression_valid = 1;
      }
      else
      {
        pressure_delta.pression_valid = 0;
      }
    }
  }
  break;

  case 31:
  {
    static unsigned long caseStartTime = 0; // Variable to store the start time of the current case
    // Check if it's the first time entering this case
    if (caseStartTime == 0)
    {
      // Record the start time
      caseStartTime = millis();
    }
    // Display pressure validation
    display.pression_validation(pressure_delta.delta, pressure_delta.pression_valid);
    // Check if 5 seconds have passed
    if (millis() - caseStartTime >= 5000)
    { // 5000 milliseconds = 5 seconds
      // Reset the start time for the next time this case is entered
      caseStartTime = 0;
      etape_test_flux = 4;
    }
  }
  break;
  case 4:
  {
    static unsigned long lastTestTime = 0;
    if (millis() - lastTestTime >= 1000)
    {
      lastTestTime = millis(); // Update the last test time
      Electrovanne.IN_ON();
      delay(4000); // a enlever
      Electrovanne.OUT_ON();
      freq_test.frequency[freq_test.testCount] = turboxy.GET_FREQUENCY();

      display.testing_frequency(freq_test.frequency[freq_test.testCount]);

      // Check if the frequency is closer to the reference value
      if (abs(freq_test.frequency[freq_test.testCount] - freq_test.reference) <= freq_test.delta_reference)
      {
        freq_test.valid = true; // Frequency is valid
      }
      else
      {
        freq_test.valid = false; // Frequency is not valid
      }

      freq_test.testCount++;

      // Check if all tests are completed
      if (freq_test.testCount >= 10)
      {
        // All tests completed, perform validation or other actions here
        // Reset test count and any other necessary variables for the next set of tests
        freq_test.testCount = 0;
        etape_test_flux = 41;
      }
    }
  }
  break;

  case 41:
  {
    static uint32_t validationStartTime = 0;
    static bool validationDisplayed = false;

    // Check if it's time to display the validation
    if (!validationDisplayed)
    {
      validationStartTime = millis();
      validationDisplayed = true;
    }

    if (millis() - validationStartTime < 5000)
    {
      // Display frequency validation
      display.frequency_validation(freq_test.frequency[10], freq_test.valid);
    }
    else
    {
      // 5 seconds have passed, reset variables and transition to the next state
      validationDisplayed = false;
      etape_test_flux = 0; // Transition to the initial state
    }
  }
  break;

  default:
    etape_test_flux = 0;
    break;
  }
}
