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
#include "dispatch.h"   //диспетчер
//TODO: необходимо меню или событийная система
uint16_t Time=0;
uint16_t FastTime=0;
uint16_t i;
uint16_t TimeStop=0;
uint16_t TimeSupply=0;
uint16_t CurrentTime=0;
uint16_t timer2=0;
uint16_t timer2_works=0;
uint16_t timerFunction=0;
uint16_t NextState=0;
int KeyCurrentCode;
//template <typename AnyType>;
//const AnyType Sum(const AnyType &a, const AnyType &b,const AnyType &c)
//{
//  return a + b + c ;
//}
//Костыли :(

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
//    KeyCode=0;
    //добавляем задачи
    AddTask(IND_Update,Idle,5,0xffff);
    AddTask(KeyScan,Idle,25,0xffff);
   AddTask(FuncINDTime,Idle,250,0);
//    AddTask(FuncINDOutput,50,50);
//    AddTask(IND_Output(1234,1));
    AddTask(StateAutomate,Idle,50,0xffff);

    sei();
    while(1){

        DispatchTask();

    }return 0;
}
