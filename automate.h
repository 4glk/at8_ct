#include <avr/io.h>
#include <avr/interrupt.h>

#include "kbd.h"
//#include "macros.h"
#include "indicator.h"

//PackedBool flags;


void StateAutomate(uint8_t KeyCode());
