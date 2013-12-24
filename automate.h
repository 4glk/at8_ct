#include <avr/io.h>
#include <avr/interrupt.h>
//#include <stdbool.h>
#include "kbd.h"
#include "indicator.h"
#include "macros.h"


extern uint16_t CurrentTime;
extern uint16_t TimeStop;
extern uint16_t TimeSupply;
extern uint16_t adc6;
extern uint16_t adc7;
void StateAutomate();
void ShowAdc6();
void ShowAdc7();
extern void AddTask (void (*taskfunc)(void), uint16_t taskdelay);
void FuncINDTime();
void FuncINDOutput();
void Furnance_sw();
void Fire_sw();
void Supply_sw();
void Timer_sw();
//extern void AddTask (void (*taskfunc)(void),void (*nextfunc)(void), u16 taskdelay, u16 taskperiod,u16 taskruns);

//ругаетс€ на точто объ€вил как функции в структуре , ладно  така€ организаци€ будет когда перейду на плюсы
/*
typedef struct {
    uint16_t tralala;
    void Furnance(void);
    void Supply();
    void Fire();
    void Timer();
}sw;
//*/
