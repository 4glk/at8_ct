/***таймер-контроллер***/

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>       //КЭП
#include "macros.h"     //описание флагов и работа с битами
#include "kbd.h"        //работа с клавиатурой
#include "adc.h"        //работа с АЦП
#include "indicator.h"  // работа с семисегментниками
#include "spi.h"        // последовательный интерфейс
#include "automate.h"   // файл конечного автомата , скоро наверное будет не нужен
#include "timer.h"      // файл таймеров
#include "compilers.h"  //откудато зачемто откручено , с чипэнабла макрос под разные компиляторы
#include "sheduler/dispatch.h"   //диспетчер
//TODO: осталось вроде только таймер допилить ну и основные функции
//+ацп
//таймер
//+диспетчер
//+кнопки
//функции автомата

//TODO: необходимо меню или событийная система
uint16_t TimeStop=0;
uint16_t TimeSupply=0;
uint16_t CurrentTime=0;
int KeyCurrentCode;
extern void doubleCountdown();
//template <typename AnyType>;
//const AnyType Sum(const AnyType &a, const AnyType &b,const AnyType &c)
//{
//  return a + b + c ;
//}
//Костыли :(
//extern void FuncINDTime();
/***Главная функция***/
int main (void)
{
	InitTimer();
	InitADC();
    InitScheduler();
    IND_Init();
    InitControl();
  // флаги нужны для флагового автомата , скоро они будут не нужны или не все
    flags.KeyPin=0;
    flags.KeyPushLong=0;
    flags.KeyState=0;
    flags.KeyPressed = 0;
    flags.KeyReleased = 1;
    flags.State_Automate=0;
    flags.SupplyAuto=0;
    flags.SupplyManual=0;
    flags.Furnace=0;        //(C,5)
    flags.NextState=0;
    flags.RunFlag=1;
    flags.TimerFlag=0;
    AddTask(IND_Update,10);
    AddTask(KeyScan,25);
    AddTask(FuncINDTime,250);
    AddTask(StateAutomate,50);
    AddTask(doubleCountdown,100);
    sei();
    while(1){
  /*//попытка запуска извращенческой переключалки по флагу переполнения таймера
        if (!(TIFR&(1<<TOV1))){
            AddTask(doubleCountdown,5);
           // (TIFR |= (1<<TOV1));
         //   (TIFR&= ~(1<<TOV1));
        }   //*/
        DispatchTask();

    }return 0;
}
