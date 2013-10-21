#include <avr/io.h>
#include <avr/interrupt.h>
#include "kbd.h"
#include "indicator.h"

extern uint16_t timer2;
extern uint16_t NextState;
extern uint16_t timer2_works;
extern uint16_t CurrentTime;
void StateAutomate();
//void DisplayHandler();
//int dispCode;
//extern void FuncINDOutput();
//extern void Idle();
//extern void ToggleBitTruba();
void ToggleSupplyManual();
void FuncINDTime();
void FuncINDOutput();
void Idle();
//void ToggleBitTruba();
void Furnance_sw();
void Fire_sw();
void Supply_sw();
void Timer_sw();
//extern void AddTask (void (*taskfunc)(void),void (*nextfunc)(void), u16 taskdelay, u16 taskperiod,u16 taskruns);
