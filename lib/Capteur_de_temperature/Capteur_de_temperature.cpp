#include "Capteur_de_temperature.h"

// Constructeur : initialise la température à 0
Capteur_de_temperature::Capteur_de_temperature(/* args */)
{
    _temperature = 0;
}

// Destructeur : actuellement vide, mais utile pour la gestion des ressources
Capteur_de_temperature::~Capteur_de_temperature()
{
}

// Méthode pour lire et calculer la température
float Capteur_de_temperature::GetTemperature()
{
    uint16_t Num_VADC_Temperature = 0;                       // Variable pour stocker la valeur lue sur l'ADC
    Num_VADC_Temperature = analogRead(PIN_VADC_Temperature); // Lecture de la valeur analogique

    float mVout = quantum_ADC * Num_VADC_Temperature;        // Conversion de la valeur ADC en tension (mV)
    float Temperature_kelvin = mVout / 10;                   // Conversion de la tension en température en Kelvin
    float Temperature_celcius = Temperature_kelvin - 273.15; // Conversion de la température de Kelvin en Celsius

    _temperature = Temperature_celcius; // Mise à jour de la température stockée
    return Temperature_celcius;         // Retourne la température en Celsius
}

// Méthode pour afficher la température sur le port série
void Capteur_de_temperature::display_temp_Serial()
{
    Serial.print("la Temperature de capteur est ");
    Serial.println(_temperature); // Affichage de la température sur le port série
}
