#include <avr/io.h>
#include <avr/interrupt.h>
//#include <stdbool.h>
#include "kbd.h"
#include "indicator.h"
#include "macros.h"

extern uint16_t timer2;
extern uint16_t NextState;
extern uint16_t timer2_works;
extern uint16_t CurrentTime;
extern uint16_t TimeStop;
extern uint16_t TimeSupply;
extern uint16_t adc6;
extern uint16_t adc7;
void StateAutomate();
void ShowAdc6();
void ShowAdc7();
//void DisplayHandler();
//int dispCode;
//extern void FuncINDOutput();
//extern void Idle();
//extern void ToggleBitTruba();
extern void AddTask(void (*taskfunc)(void),void (*nextfunc)(void),uint16_t taskdelay,uint16_t nextdelay,uint16_t taskruns);
extern void ResetTask(void (*resfunc)(void));
void ToggleSupplyManual();
void FuncINDTime();
void FuncINDOutput();
void Idle();
void AddCurrentTime();
//void ToggleBitTruba();
void Furnance_sw();
void Fire_sw();
void Supply_sw();
void Timer_sw();
//extern void AddTask (void (*taskfunc)(void),void (*nextfunc)(void), u16 taskdelay, u16 taskperiod,u16 taskruns);

//ругается на точто объявил как функции в структуре
/*
typedef struct {
    uint16_t tralala;
    void Furnance(void);
    void Supply();
    void Fire();
    void Timer();
}sw;
//*/
