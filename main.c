/***таймер-контроллер***/
// TODO: куча задач
//+ разобраться с проблемой функции делэй , скорее всего трабла в переносимости глобальной переменной i или z , трабла была
//+ в использовании внутренней функции и библиотечной функции avr-gcc
//- изменить полностью вывод на дисплей , организовать буффер вывода с возможностью вывода символов , и использование
//- сдвигового регистра в частности 74hc164 или 74hc595
//- пашган с чипэнабла помог своим драйвером , теперь это не проблема
//- ввести яркость дисплея посредством изменения значения счетчика , прикрутить к ацп датчик освещенности
//- организовать работу со строками , в частности бегущую строку (class string) , готово в пашгановском
//- разобраться с антидребезгом кнопок , доработать систему с кодами кнопок , защелка , а также ввести функции при удержании кнопок
//- доработать ацп , чтобы небыло лишних преобразований по пути к дисплею , средним арефметическим от 10
//- разработать меню режимов , настроек и работу с ППЗУ
//- event-system !!!!
//- state (состояние)-> event (событие) -> state (состояние) -> handler(обработчик)
//- event-sources[1..x] -> loop order (кольцевая очередь) -> dipatcher -> handlers

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>
#include "macros.h"     //описание флагов и работа с битами
#include "kbd.h"        //работа с клавиатурой
#include "adc.h"
#include "indicator.h"
#include "spi.h"
#include "automate.h"
#include "timer.h"
#include "compilers.h"




//////////////   *******************переменные , почистить глобальные переменные , работать через указатели
/*
volatile int adc_but,BUTTON;
volatile int adc6,adc7;
volatile int ch_st=0; // 0 - 1 channel, 1 - 2 channel
volatile int counti=0,count1=0,count2=0;
int adc6_a=0,adc7_a=0; //переменные для отображения регулирования таймера
volatile unsigned char segcounter = 0;
volatile int display1 = 0;
volatile int display2 = 0;
int count_st=0;
int z=10,i=0; // на задержку индикации для управления яркостью

///////////////    **************функции
//void delay(int x);				//функция задержки
int trigger(int btn,int port);	//функция переключения

//*/

uint16_t i;
/***Главная функция***/
int main (void)
{

 //   TCNT1 = 57724;
 //   flags.KeyPressed=0;
//	InitDisplay();
	InitTimer();
//	InitADC();
//	InitControl();
	//TODO: нормальный обработчик событий (пока готов флаговый автомат в пашгановском)

	  //инициализация индикатора и АЦП
  IND_Init();
//  ADC_Init();
  InitControl();
  //PackedBool flags;

  //инициализация таймера Т0
  TIMSK = (1<<TOIE0)|(1<<TOIE1); // переполнение
  TCCR0 = (1<<CS02)|(0<<CS01)|(1<<CS00); // предделитель 1024
  TCNT0 = TCNT0_const;
    flags.KeyPin=0;
    flags.KeyPushLong=0;
    flags.KeyState=0;
    flags.KeyPressed = 0;
    flags.KeyReleased = 1;
    flags.State_Automate=0;
 //   DDRC=0b00111000;
  sei();
while(1){
   // IND_Output(23332,0);
    //IND_OutputFormatChar("HEFH",1,1);
    //IND_OutputFormatChar("ABCD",6,4);
   // IND_OutputFormat(12345678, 1,  1,  8);
    if (flags.State_Automate)StateAutomate(KeyCode());
        /* // устаревший обработчик , суперцикл
	display1=count1; if (display1==0) {display1=adc6_a;delay(2000);} //отображение счетчика ,
	display2=count2; if (display2==0) {display2=adc7_a;delay(2000);} //если 0 то показать выставленное значение
	if (adc6_a!=adc6) {display1=adc6;delay(2000);adc6_a=adc6;}      //если крутим ручку , то показать это значение
	if (adc7_a!=adc7) {display2=adc7;delay(2000);adc7_a=adc7;}       // всю эту херню надо загнать в прерывание индикации
	/////////    ***********Счетчик старт стоп , автомат ручное (одно и тоже короче пока что)**********
	// это все перелопатить , сделать через свитч кодов клавиш хотябы для наглядности
	if (count_btn&&(count_st==0)){delay(150);if (count_btn&&(count_st==0));count_st=1;delay(750);}
	if (count_btn&&(count_st==1)){delay(150);if (count_btn&&(count_st==1));count_st=0;CBC(3);counti=0;delay(750);} //остановка таймера
	if (podacha_btn&&(count_st==0)) {trigger(podacha_btn,3);}
	//  *
	if ((ch_st==1)&&(count_st==1)){PORTC|=(1<<PC3);}
	if ((ch_st==0)&&(count_st==1)){PORTC&= ~(1<<PC3);}
	//    *
	//////    ***********************Труба переключатель О_о ***********
	if (truba_btn){trigger(truba_btn,5);}
	//////////   *********горелка************
	if (fire_btn){trigger(fire_btn,4);} //1

	//*/

}return 0;
}

ISR(TIMER0_OVF_vect) // на осциллографе в протеусе 10мс (10kHz)
{
  //  PackedBool flags;
  TCNT0 = TCNT0_const;  //7812   217  //8000000/1024
 // IND_Output(1234,3);
  IND_Update();
 // if(1){
  if(~PINC&0b00000111){ // обработчик нажатия
    flags.KeyReleased=0;
        if (++i > 25 ) {      //короткое нажатие 100 миллисекунд
            if (!flags.KeyPressed){flags.KeyPressed = 1;flags.KeyPin=(~PINC&0b00000111);}
               if ( i >100 ){  //длинное нажатие 3 секунды
                 if (!flags.KeyPushLong){

                    flags.KeyPushLong=1;
                    KeyState();
                 }
               }
        }
    }
    else {
        i=0;
        if (!flags.KeyReleased) {flags.KeyReleased=1;}
        KeyState();
    }
    if (CH(C,4)) {CB(C,4);}else SB(C,4);// на осциллографе в протеусе 10мс(100гц)
}
