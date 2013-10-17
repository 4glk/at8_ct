#include "adc.h"
//TODO: �������� ����������� ������� , ���� �������� ��������������� (���������� ������������)

ISR (ADC_vect){
	//ADMUX  |= (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0);adc6=ADCW;
	//ADMUX  |= (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0);adc7=ADCW;
if (ADMUX==6){
		ADMUX=7; // ���������� ���� ADC6
		adc6=ADCW/10; // ����� ��������� � adc7
		ADCSRA|=0x40;// // ������ ��������� �������������
		}

	else {
		ADMUX=6; // ���������� ���� ADC7
		adc7=ADCW/10*60; // ����� ��������� ADC6
		ADCSRA|=0x40; // ������ ��������� �������������
	}
}

void InitADC(){
//	cli();
	ADCSRA |=  (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar
	ADMUX |= (1 << REFS0)|(0<<REFS1); // Set ADC reference to AVCC
   	ADCSRA |= (1 << ADFR);  // Set ADC to Free-Running Mode
   	ADCSRA |= (1 << ADEN);  // Enable ADC
   	ADCSRA |= (1 << ADSC);// Start A2D Conversions
	ADCSRA |= (1 << ADIE);//��� 3 � ADIE (ADC Interrupt Enable) � ��� ���������� ���������� ���������������� ��������������� : 1 � ���������, 0 � ���������.
//	sei();
}

