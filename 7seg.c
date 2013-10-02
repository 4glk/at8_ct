#include "7seg.h"
//TODO: влепить пашгановский драйвер и добавить в него отображение символов и строк
char SEGMENT[ ] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
//****//////// ************Обработчик прерывания по переполнению таймера2
//segcounter = 0;
/*
ISR (TIMER2_OVF_vect)
{
PORTD = 0xFF; //гасим все разряды
PORTB = (1 << segcounter); //выбираем следующий разряд
switch (segcounter){ 						// здесь выделяем минуты , секунды из одного значения секунд
	case 0:PORTD = ~(SEGMENT[display1  % 6000/600]);delay(z);break; // здесь раскладываем число на разряды
	case 1:PORTD = ~(SEGMENT[display1  % 600 /60 ]);CB(PORTD,7);delay(z);break; // +точка
	case 2:PORTD = ~(SEGMENT[display1 % 60 /10]);delay(z);break;					// выделяем десятки секунд 5 максимальное значение
	case 3:PORTD = ~(SEGMENT[display1 % 10]);delay(z);break;
}

switch (segcounter){
	case 4:PORTD = ~(SEGMENT[display2 % 6000 / 600]);delay(z);break; // здесь раскладываем число на разряды
	case 5:PORTD = ~(SEGMENT[display2 % 600 / 60]);CB(PORTD,7);delay(z);break;
	case 6:PORTD = ~(SEGMENT[display2 % 60 / 10]);delay(z);break;
	case 7:PORTD = ~(SEGMENT[display2 % 10]);delay(z);break;
}
if ((segcounter++) > 6) segcounter = 0;
	i--;
}
//*/


//* вариант 2
ISR (TIMER2_OVF_vect)
{
PORTD = 0xFF; //гасим все разряды
PORTB = (1 << segcounter); //выбираем следующий разряд
switch (segcounter){ 						// здесь выделяем минуты , секунды из одного значения секунд
	case 0:PORTD = ~(SEGMENT[display1  % 6000/600]);break; // здесь раскладываем число на разряды
	case 1:PORTD = ~(SEGMENT[display1  % 600 /60 ]);CB(D,7);break; // +точка
	case 2:PORTD = ~(SEGMENT[display1 % 60 /10]);break;					// выделяем десятки секунд 5 максимальное значение
	case 3:PORTD = ~(SEGMENT[display1 % 10]);break;
}

switch (segcounter){
	case 4:PORTD = ~(SEGMENT[display2 % 6000 / 600]);break; // здесь раскладываем число на разряды
	case 5:PORTD = ~(SEGMENT[display2 % 600 / 60]);CB(D,7);break;
	case 6:PORTD = ~(SEGMENT[display2 % 60 / 10]);break;
	case 7:PORTD = ~(SEGMENT[display2 % 10]);break;
}
if ((segcounter++) > 6) segcounter = 0; // считает от 0 до 7 , соответственно кол-во значений равно 8
	i--;
}


//*/
