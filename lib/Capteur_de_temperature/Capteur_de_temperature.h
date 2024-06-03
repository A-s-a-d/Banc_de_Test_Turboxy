#ifndef CAPTEUR_DE_TEMPERATURE_H
#define CAPTEUR_DE_TEMPERATURE_H

#include <Arduino.h>
#include "ADC.h"

// Définition de la broche ADC pour le capteur de température
#define PIN_VADC_Temperature A2

class Capteur_de_temperature
{
private:
    float _temperature; // Variable pour stocker la température mesurée

public:
    Capteur_de_temperature(/* args */); // Constructeur
    ~Capteur_de_temperature();          // Destructeur

    float GetTemperature();     // Méthode pour obtenir la température actuelle
    void display_temp_Serial(); // Méthode pour afficher la température sur le port série
};

#endif
