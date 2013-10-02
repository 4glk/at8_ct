#include "init.h"
void InitControl(){
	DDRC=0b00111000;
	//DDRC |= (1 << PC1)|(1 << PC2)|(1 << PC3)|(1 << PC4)|(1 << PC5)|(1 << PC6);
	PORTC=0b00000111;
}


