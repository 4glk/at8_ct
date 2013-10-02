//#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>
//#include "macros.h"

//extern int trigger(int btn,int port);
//extern void delay(int x);



#include <avr/io.h>
#include <avr/interrupt.h>
#include "macros.h"
//PackedBool flags;
void InitControl();
uint8_t KeyCode();
void KeyState();


