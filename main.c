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
#include "compilers.h"  //откудато зачемто откручено
#include "dispatch.h"   //диспетчер

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

void ToggleSupplyManual();
void FuncINDTime();
void FuncINDOutput();
/***Главная функция***/
int main (void)
{
	InitTimer();
	InitADC();
    InitScheduler();
  IND_Init();
  InitControl();
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
    AddTask(IND_Update,5,5);
    AddTask(KeyScan,25,25);
    AddTask(FuncINDTime,50,50);
    AddTask(FuncINDOutput,50,50);
  sei();
while(1){

   DispatchTask();

}return 0;
}
void FuncINDTime(){
    IND_Time(CurrentTime,5);
}

void FuncINDOutput(){
    IND_Output(1234,1);
}

void ToggleSupplyManual(){
    TB(C,3);
}
