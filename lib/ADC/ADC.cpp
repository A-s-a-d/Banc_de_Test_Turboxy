#include "ADC.h"
/*
resolution ADC en bits, reference de tension ADC
*/
void begin_ADC()
{
    analogReadResolution(ADC_resolution); // resolution ADC en bits
    analogReference(ADC_reference);       // reference de tension ADC
}