#include "adc.h"
//TODO: добавить программные фильтры , типа среднего арефметического (прикрутить пашгановский)

ISR (ADC_vect){
    AdcMean();
	//ADMUX  |= (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0);adc6=ADCW;
	//ADMUX  |= (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0);adc7=ADCW;
	/*
if (ADMUX==6){
		ADMUX=7; // Перекючить вход ADC6
		adc6=ADCW/10; // снять показания в adc7
		ADCSRA|=0x40;// // Начать следующее преобразоание (1<<ADSC)
		}

	else {
		ADMUX=6; // Перекючить вход ADC7
		adc7=ADCW/10*60; // снять показания ADC6
		ADCSRA|=0x40; // Начать следующее преобразоание (1<<ADSC)
	}
	//*/
}

void AdcTaking(){
 //   AdcMean();
}

void AdcMean(){
    static uint8_t counti = 0;
//    uint16_t adcTemp=0;
//    uint16_t adc_buf;
 //   uint16_t adc_result;
//    adcTemp = ADCL;
//    adcTemp |=(ADCH<<8);
//    adc_buf+=adcTemp;
        ADCSRA|=(1<<ADSC);
      if (counti!=0) adc_buf+=ADCW; //опять костыли (((
      counti++;
//    if (counti==8)
//   одно значение попадает в другое ((( из за того что мукс переключается в след прерывании, а значение берет еще здесь (
    if (counti == 9){
        adc_result = (adc_buf>>3);
 //       adc_result = (adc_buf/8);
        adc_buf = 0;
        counti = 0;
        if (ADMUX==6){
            adc6=adc_result;
            ADMUX=7;
         //   ADCSRA|=(1<<ADSC);

        }//*
        else {
            adc7=adc_result*10;
            ADMUX=6;
         //   ADCSRA|=(1<<ADSC);
        }//*/
    }
 // ADCSRA |= (1<<ADSC);
 //   adc_buf+=ADCW;
  //  counti++;

}

void InitADC(){
//	cli();
	ADCSRA |=  (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar
	ADMUX  |= (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0);    // adc6=ADCW;
	ADMUX |= (1<<ADLAR)|(1 << REFS0)|(0<<REFS1); // Set ADC reference to AVCC
//   	ADCSRA |= (1 << ADFR);  // Set ADC to Free-Running Mode
   	ADCSRA |= (1 << ADEN);  // Enable ADC
   	ADCSRA |= (1 << ADSC);// Start A2D Conversions
	ADCSRA |= (1 << ADIE);//Бит 3 – ADIE (ADC Interrupt Enable) – бит разрешения прерывания аналого–цифрового преобразователя : 1 – разрешено, 0 – запрещено.
//	sei();
}

/*
    ADMUX |= (1<<REFS0)|(1<<ADLAR)|(0<<MUX1)|(1<<MUX0); //ADCH,adsc
    ADCSRA |= (1<<ADEN)|(1<<ADSC)|(0<<ADATE)|(1<<ADIF)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
//    ADCSRB |= (0<<ACME)|(0<<ADTS2)|(0<<ADTS1)|(0<<ADTS0);
//    DIDR0 |= (0<<ADC0D)|(0<<ADC2D)|(0<<ADC3D)|(0<<ADC1D)|(0<<AIN1D)|(0<<AIN0D);
    int state=0;
    for(;;){
    st=PINB & 0b001000;
    if (!st){
        if (state==0) {
         *timer_ptra=adc_result;
            state=1;
        }
        if (state==1){
       *timer_ptrb=adc_result;
            state=0;
        }
    }
    }
    return 0;
}

ISR(ADC_vect){
    ADCSRA|=(1<<ADSC);
  static uint8_t count = 0;
  //считываем результат преобразования АЦП
//  adcTemp = ADCL;
 // adcTemp |=(ADCH<<8);
    adc_buf+=ADCH;
  //adcValue  += adcTemp;
  //если накопили сумму 8-ми значений - делим на 8
  //сохраняем в буфере, обнуляем счетчик и аккумулятор
    count++;
  if (count == 8){
    adc_result = (adc_buf>>3);
    adc_buf = 0;
    count = 0;
  }
  ADCSRA |= (1<<ADSC);
}
//*/
