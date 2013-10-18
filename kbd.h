#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "macros.h"

void InitControl();
uint8_t KeyCode();
void KeyState();
void KeyScan();
//extern uint16_t i;
uint16_t i;
extern int KeyCurrentCode;
//extern void AddTask (void (*taskfunc)(void), u16 taskdelay, u16 taskperiod);
extern void StateAutomate();
//*(KeyCodePointer) = &KeyCurrentCode;
