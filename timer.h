
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>
//#include "macros.h"
#define TCNTCC 57724
extern int count_st;
extern volatile int adc6,adc7;
extern volatile int ch_st; // 0 - 1 channel, 1 - 2 channel
extern volatile int counti,count1,count2;
