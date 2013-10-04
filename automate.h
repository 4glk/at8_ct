#include <avr/io.h>
#include <avr/interrupt.h>

#include "kbd.h"
//#include "macros.h"
#include "indicator.h"

//PackedBool flags;
extern uint16_t timer2;
extern uint16_t NextState;
extern uint16_t timer2_works;

void StateAutomate();
//extern enum InfoString();
