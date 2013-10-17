
// Счетчик времени , минуты и секунды

#include "timer.h"


ISR( TIMER1_OVF_vect )  //на осциллограффе в протеусе ровно 1 сек ^^
{
	TCNT1=57724;
//TODO: разобраться с переменными времени , кажется что есть лишние , время состояний можно в ацп закинуть ,
// а здесь просто присваивать
if (flags.SupplyAuto==1){
if (CurrentTime!=0){
		CurrentTime--;
	}
	else{
		if (flags.ADC_Channel==0){
			CurrentTime=adc6;
			TimeSupply=CurrentTime+1;
			flags.ADC_Channel=1;
			SB(C,3);
		}
			else{
			CurrentTime=adc7;
			TimeStop=CurrentTime+1;
			flags.ADC_Channel=0;
			CB(C,3);
		}

	}

if (flags.ADC_Channel==0) {TimeStop--;}
	else {TimeSupply--;}
}
//*/
}
void InitTimer(){

  TIMSK = (1<<TOIE0)|(1<<TOIE1)|(1<<TOIE2); // переполнение
  TCCR0 = (1<<CS02)|(0<<CS01)|(1<<CS00); // предделитель 1024
  TCNT0 = TCNT0_const;
  TCCR2 = (1<<CS02)|(0<<CS01)|(1<<CS00);
	TCCR1B = (1<<CS12)|(0<<CS11)|(1<<CS10); // настраиваем делитель 100=256 101=1024
//	TIMSK = (1<<TOIE1); // разрешаем прерывание по переполнению таймера 1 // перенесено в главный файл
	TCNT1 = 57724;        // выставляем начальное значение TCNT1 64456 57724
}

ISR(TIMER0_OVF_vect) // на осциллографе в протеусе 10мс (10kHz)
{
  TCNT0 = TCNT0_const;  //7812   217  //8000000/1024
    (CH(C,4))?CB(C,4):SB(C,4);// на осциллографе в протеусе 10мс(100гц),теперь восемь оО
}
