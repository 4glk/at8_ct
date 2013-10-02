#ifndef MACROS_
#define MACROS_

/*************управление портами
//стара€ верси€
#define SB(x,y) (x|=(1<<y))		//setbit (PORTx,y)
#define CB(x,y)	(x&= ~(1<<y))	//clearbit
#define TB(x,y) (x^=(1<<y))		//togglebit
#define CH(x,y) (x&(1<<y))		//checkbit
//*/

//*
#define SB(port,bit) (PORT##port|=(1<<bit))		//setbit (port,bit) приклеим это слово порт куда надо и будет проще
#define CB(port,bit) (PORT##port&= ~(1<<bit))   //clearbit а лучше конечно написать порт и бит шоб пон€тнее было
#define TB(port,bit) (PORT##port^=(1<<bit))		//togglebit и это , терь не надо писать PORTC  терь только C и все
#define CH(port,bit) (PIN##port&(1<<bit))		//checkbit CH(B,3) так терь оно будет гл€детьс€
//*/
// это все прекрасно , но как пощупать бит порта командочкой PIN ?
// а то циклитс€ родима€ в теле переключател€ на антидребезге

// тоже самое дл€ порта C

#define SBC(x) (PORTC|=(1<<x))		//setbit
#define CBC(x)	(PORTC&= ~(1<<x))	//clearbit
#define TBC(x) (PORTC^=(1<<x))		//togglebit
#define CHC(x) (PINC&(1<<x))		//checkbit PIN  на чеке , а не PORT

/*/ немного красотищи из scmRTOS pin_macros.h  (AVR/avr-gcc)
#define PM_SETL(port,bit,dummy) (PORT##port &= ~(1<<(bit))) // так вот в дефайнах строка склеиваетс€
#define PM_SETH(port,bit,dummy) (PORT##port |= (1<<(bit)))  // ##
#define PM_SET(port,bit,val) PM_SET##val(port,bit,dummy)
#define ON(x) PM_SET(x)
#define SET(x) PM_SETH(x)
#define CLR(x) PM_SETL(x)
//*/

 // значение калибровки таймера , секунда тики

/******************кнопки********************
#define KP1 (PINC&(1<<PC0))   //KP = Key Port а чо бы так не сделать что бы меньше в глазах р€било ?
#define KP2 (PINC&(1<<PC1))   //CHC(1)
#define KP3 (PINC&(1<<PC2))   //CHC(2)
#define truba_btn (!KP3&&KP2&&KP1)    //100
#define fire_btn (KP3&&!KP2&&KP1)     //010
#define podacha_btn (KP3&&KP2&&!KP1)  //001
#define avtomat_btn (!KP3&&KP2&&!KP1) //101
#define count_btn (KP3&&!KP2&&!KP1)   //011
#define plus1_btn (!KP3&&!KP2&&KP1)   //110
#define plus2_btn (!KP3&&!KP2&&!KP1)  //111


//enum boolean { L = 0, H };
//    ******************************************/
// и енумом коды клавиш сразу приписать
/*
typedef enum f {           // потом объ€вить типа Btn KeyCode и переключать последнюю как int
    truba_btn=4,      //0 или можно +1 шоб с нулем не путатьс€
    fire_btn=2,       //1 или вообще каждому свой присвоить
    podacha_btn=1,    //2 или в обычных скобках хз
    avtomat_btn=5,    //3 тупо из бин кодов номер клавиши получаетс€
    count_btn=3;      //4
    //plus1_btn=6,      //5
    //plus2_btn=7       //6
};
//*/

/***********стара€ сишна€ верси€*****************************************************
#define truba_btn (!(PINC&(1<<PC2)))&&(PINC&(1<<PC1))&&(PINC&(1<<PC0))          //100
#define fire_btn ((PINC&(1<<PC2)))&&(!(PINC&(1<<PC1)))&&(PINC&(1<<PC0))         //010
#define podacha_btn ((PINC&(1<<PC2)))&&((PINC&(1<<PC1)))&&(!(PINC&(1<<PC0)))    //001
#define avtomat_btn (!(PINC&(1<<PC2)))&&((PINC&(1<<PC1)))&&(!(PINC&(1<<PC0)))   //101
#define count_btn ((PINC&(1<<PC2)))&&(!(PINC&(1<<PC1)))&&(!(PINC&(1<<PC0)))     //011
///+********************************************************************************/
#define truba_off CBC(5)//(PORTC&= ~(1<<PC5)) парочка типа булеана
#define truba_on SBC(5)//(PORTC|=(1<<PC5))
#endif // MACROS_
///----------------------------------------------
///-----это мой битмакрос
///----------------------------------------------
/*
#define SB(port,bit) (PORT##port|=(1<<bit))		//setbit (port,bit)
#define CB(port,bit) (PORT##port&= ~(1<<bit))   //clearbit CH(B,3) так терь оно будет гл€детьс€
#define TB(port,bit) (PORT##port^=(1<<bit))		//togglebit
#define CH(port,bit) (PIN##port&(1<<bit))		//checkbit
//*/
#include <stdbool.h>

#pragma once
//*
typedef struct { //булеановы переменные , зачем тратить на каждый флаг по байту ?
  bool State_Automate:1;
  bool KeyPressed:1;
  bool KeyReleased:1;
  bool KeyPushLong:1;
  bool f4:1;
  uint8_t  KeyPin:4;
  bool KeyState:1;
  //bool f6:1;
  //bool f7:1;
 } PackedBool;
PackedBool flags;
//*/



