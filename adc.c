#include "adc.h"
//Прерывание ADC
//TODO: добавить программные фильтры , типа среднего арефметического (прикрутить пашгановский)

ISR (ADC_vect){
	//ADMUX  |= (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0);adc6=ADCW;
	//ADMUX  |= (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0);adc7=ADCW;
if (ADMUX==6){
		ADMUX=7; // Перекючить вход ADC6
		adc6=ADCW/10; // снять показания в adc7
		ADCSRA|=0x40;// // Начать следующее преобразоание
		}

	else {
		ADMUX=6; // Перекючить вход ADC7
		adc7=ADCW/10*60; // снять показания ADC6
		ADCSRA|=0x40; // Начать следующее преобразоание
	}
// вообще не рекомендуется использовать младшие биты ацп из-за шумов ,
//ADCW = 12 БИТ АЦП
//ADCH = 8  старшие 8 бит
//ADCL = 4  младшие 4 бита
// или наоборот ?? оО
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
	ADCSRA |= (1 << ADIE);//Бит 3 – ADIE (ADC Interrupt Enable) – бит разрешения прерывания аналого–цифрового преобразователя : 1 – разрешено, 0 – запрещено.
//	sei();
}


// пашгановский ацп
/*
void ADC_Init(void)
{
  //ион - внутренний 2.56 В, выравнивание вправо, нулевой канал
  ADMUX = (1<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0);// последние три бита номер канала в двоичной
  //вкл. ацп, режим непрерывного преобр., разрешение прерывания, частота преобр. = FCPU/
  ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADIE)|(1<<ADPS2)|(0<<ADPS1)|(0<<ADPS0);//(0<<ADFR)|; --ADCSR
  //запускаем преобразование
  ADCSRA |= (1<<ADSC);
}

//-------******************************************************************************

//буфер, в который мы храним усредненное значение напряжения
volatile unsigned int adcValueBuf = 0;
ISR(ADC_vect)
{
  unsigned int adcTemp;
  static unsigned int adcValue = 0;
  static unsigned char count = 0;

  //считываем результат преобразования АЦП
  adcTemp = ADCL;
  adcTemp |=(ADCH<<8);

  adcValue  += adcTemp;

  //если накопили сумму 8-ми значений - делим на 8
  //сохраняем в буфере, обнуляем счетчик и аккумулятор
  count++;
  if (count == 8){
    adcValueBuf = (adcValue>>3);
    adcValue = 0;
    count = 0;
  }
  ADCSRA |= (1<<ADSC);
}

//----*****************************************************************************
//возвращает значение буфера
//на время считывания буфера запрещаются прерывания
//для атомарности операции
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
