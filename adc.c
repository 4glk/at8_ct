#include "adc.h"
//���������� ADC
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
// ������ �� ������������� ������������ ������� ���� ��� ��-�� ����� ,
//ADCW = 12 ��� ���
//ADCH = 8  ������� 8 ���
//ADCL = 4  ������� 4 ����
// ��� �������� ?? ��
}

void InitADC(){
//	cli();
	ADCSRA |=  (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar
	ADMUX |= (1 << REFS0)|(0<<REFS1); // Set ADC reference to AVCC
	// no left ajustment needed in 10 bit mode!
	//ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading
   	// No MUX values needed to be changed to use ADC0
	//ADMUX = 6;// |= (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0); //ADC6
	//ADMUX  |= (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0); //ADC7
   	ADCSRA |= (1 << ADFR);  // Set ADC to Free-Running Mode
   	ADCSRA |= (1 << ADEN);  // Enable ADC
   	ADCSRA |= (1 << ADSC);// Start A2D Conversions
	ADCSRA |= (1 << ADIE);//��� 3 � ADIE (ADC Interrupt Enable) � ��� ���������� ���������� ���������������� ��������������� : 1 � ���������, 0 � ���������.
//	sei();
}


// ������������ ���
/*
void ADC_Init(void)
{
  //��� - ���������� 2.56 �, ������������ ������, ������� �����
  ADMUX = (1<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0);// ��������� ��� ���� ����� ������ � ��������
  //���. ���, ����� ������������ ������., ���������� ����������, ������� ������. = FCPU/
  ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADIE)|(1<<ADPS2)|(0<<ADPS1)|(0<<ADPS0);//(0<<ADFR)|; --ADCSR
  //��������� ��������������
  ADCSRA |= (1<<ADSC);
}

//-------******************************************************************************

//�����, � ������� �� ������ ����������� �������� ����������
volatile unsigned int adcValueBuf = 0;
ISR(ADC_vect)
{
  unsigned int adcTemp;
  static unsigned int adcValue = 0;
  static unsigned char count = 0;

  //��������� ��������� �������������� ���
  adcTemp = ADCL;
  adcTemp |=(ADCH<<8);

  adcValue  += adcTemp;

  //���� �������� ����� 8-�� �������� - ����� �� 8
  //��������� � ������, �������� ������� � �����������
  count++;
  if (count == 8){
    adcValueBuf = (adcValue>>3);
    adcValue = 0;
    count = 0;
  }
  ADCSRA |= (1<<ADSC);
}

//----*****************************************************************************
//���������� �������� ������
//�� ����� ���������� ������ ����������� ����������
//��� ����������� ��������
unsigned int ADC_GetBuf(void)
{
  unsigned int tmp;
  unsigned char saveState = SREG;
  cli();
  tmp = adcValueBuf;
  SREG = saveState;
  return tmp;
}
//*/
