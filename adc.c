#include "adc.h"
//TODO: добавить программные фильтры , типа среднего арефметического (прикрутить пашгановский)

ISR (ADC_vect){
    AddTask(AdcMean,Idle,100,0,0);   //отошлю в диспетчер гы гы , главное чтоб он успевал отработать , до того как новое придет
 //   AdcMean();  //медленный диспетчер может засратьс€ (
}

void AdcTaking(){
 //   AdcMean();
}

void AdcMean(){
    static uint8_t counti = 0;
        ADCSRA|=(1<<ADSC);
      if (counti!=0) adc_buf+=ADCW; //оп€ть костыли (((
      counti++;
//TODO:шатает ацп, исправить
    if (counti == 9){
        adc_result = (adc_buf>>3);
        adc_buf = 0;
        counti = 0;
        if (ADMUX==6){
            if (adc6!=adc_result);
            adc6=adc_result;
            ResetTask(FuncINDTime);
            AddTask(ShowAdc6,FuncINDTime,50,1500,0);
            ADMUX=7;
        }
        else {
           // adc7=adc_result*10;
            if (adc7!=adc_result);
            adc7=adc_result;
            ResetTask(FuncINDTime);
            AddTask(ShowAdc7,FuncINDTime,50,1500,0);
            ADMUX=6;
        }
    }
}



void InitADC(){
//	cli();
	ADCSRA |=  (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar
	ADMUX  |= (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0);    // adc6=ADCW;
	ADMUX |= (1<<ADLAR)|(1 << REFS0)|(0<<REFS1); // Set ADC reference to AVCC
//   	ADCSRA |= (1 << ADFR);  // Set ADC to Free-Running Mode
   	ADCSRA |= (1 << ADEN);  // Enable ADC
   	ADCSRA |= (1 << ADSC);// Start A2D Conversions
	ADCSRA |= (1 << ADIE);//Ѕит 3 Ц ADIE (ADC Interrupt Enable) Ц бит разрешени€ прерывани€ аналогоЦцифрового преобразовател€ : 1 Ц разрешено, 0 Ц запрещено.
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
  //считываем результат преобразовани€ ј÷ѕ
//  adcTemp = ADCL;
 // adcTemp |=(ADCH<<8);
    adc_buf+=ADCH;
  //adcValue  += adcTemp;
  //если накопили сумму 8-ми значений - делим на 8
  //сохран€ем в буфере, обнул€ем счетчик и аккумул€тор
    count++;
  if (count == 8){
    adc_result = (adc_buf>>3);
    adc_buf = 0;
    count = 0;
  }
  ADCSRA |= (1<<ADSC);
}
//*/
