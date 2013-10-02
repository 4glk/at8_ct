#include <avr/interrupt.h>
#include <avr/io.h>
#include "macros.h"

//#ifndef 7SEG_H
//#define 7SEG_H

//#endif

extern volatile int display1;
extern volatile int display2;
extern int z,i;

extern volatile unsigned char segcounter;
extern void delay(int x);  //функция задержки нихатит нормально работать после разбиения
                            //и не хотела работать в вайле триггера в цикле удержания кнопки
                            // а они через диоды и получается двойные/тройные
                            // так что там придется воткнуть счетчик циклов в сравнении
