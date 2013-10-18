#ifndef MACROS_
#define MACROS_

/*************управление портами
//стара€ верси€
#define SB(x,y) (x|=(1<<y))		//setbit (PORTx,y)
#define CB(x,y)	(x&= ~(1<<y))	//clearbit
#define TB(x,y) (x^=(1<<y))		//togglebit
#define CH(x,y) (x&(1<<y))		//checkbit
//*/
#define TCNT0_const 0xd9 //217(0xEC,236 дл€ 400√ц) //5 мс дл€ 8 бит таймера на 8ћгц 200 √ц, 2,5мс на 16ћгц 400√ц
#define TCNTCC 57724 //0xe17c 1√ц 1 сек на 16 бит таймер на 8 ћгц
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

/******************кнопки********************----//это все тоже устарело , код клавиши теперь хранитс€ в flags.KeyPin
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
//#define truba_off CBC(5)//(PORTC&= ~(1<<PC5)) парочка типа булеана
//#define truba_on SBC(5)//(PORTC|=(1<<PC5))
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
  bool State_Automate:1;    //обработчик
  bool KeyPressed:1;        //флаг нажати€ клавиши
  bool KeyReleased:1;       //флаг отпускани€ клавиши
  bool KeyPushLong:1;       //флаг долгово нажати€ клавиши
  bool KeyState:1;          //флаг состо€ни€ клавиши
  uint8_t  KeyPin:4;        //здесь код клавиши
  bool Fire:1;            //флаг горелки
  bool Furnace:1;         //флаг циркул€рной печи
  bool SupplyManual:1;
  bool SupplyAuto:1;          //флаг подачи
  bool ADC_Channel:1;      // канал ацп
  bool NextState:1;
  bool RunFlag:1;
 } PackedBool;
PackedBool flags;
int *KeyCodePointer;
//*/



