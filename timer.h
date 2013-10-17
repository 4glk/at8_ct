
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>
#include "macros.h"
void InitTimer();
extern uint16_t i;
extern void KeyState();
extern uint16_t TimeStop;
extern uint16_t TimeSupply;
extern uint16_t CurrentTime;
extern uint16_t timer2;
extern int adc6,adc7;
extern void KeyScan();
//extern uint16_t Time,FastTime;
//extern uint8_t KeyCode();
extern void IND_Update();
extern void IND_Time(uint16_t CurrentTime,uint8_t position);
//extern int count_st;
//extern volatile int adc6,adc7;
//extern volatile int ch_st; // 0 - 1 channel, 1 - 2 channel
//extern volatile int counti,count1,count2;
