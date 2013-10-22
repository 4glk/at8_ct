#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t adc6,adc7;//данные с каналов ацп
void InitADC();
void AdcTaking();
void AdcMean();
uint16_t adc_buf;
uint16_t adc_result;
//uint8_t counti = 0;
