#include <avr/io.h>
#include <avr/interrupt.h>
#include "macros.h"
void InitTimer();
void doubleCountdown();
extern void KeyState();
extern uint16_t TimeStop;
extern uint16_t TimeSupply;
extern uint16_t CurrentTime;
extern uint16_t adc6,adc7;
extern void KeyScan();
extern void IND_Update();
extern void IND_Time(uint16_t CurrentTime,uint8_t position);
extern void AddTask (void (*taskfunc)(void), uint16_t taskdelay);
