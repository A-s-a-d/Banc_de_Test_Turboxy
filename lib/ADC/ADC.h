#ifndef ADC_H
#define ADC_H

#include <Arduino.h>

#define AREF  3.29         // valeur de reference externe
#define quantum_ADC  0.195 // quantam ADC en mV, depends de Aref. 0.2008056641 = Aref/2**ADC_resolution si Aref = 3.29V

#define ADC_resolution 14         // resolution de ADC en bits, max 14 bits
#define ADC_reference AR_EXTERNAL // reference de tension externe, option : AR_INTERNAL pour interne 1.5V et AR_DEFAULT pour VCC defaut.

void begin_ADC();
#endif