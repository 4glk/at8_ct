#ifndef MACROS_
#define MACROS_

/*************���������� �������
//������ ������
#define SB(x,y) (x|=(1<<y))		//setbit (PORTx,y)
#define CB(x,y)	(x&= ~(1<<y))	//clearbit
#define TB(x,y) (x^=(1<<y))		//togglebit
#define CH(x,y) (x&(1<<y))		//checkbit
//*/
#define TCNT0_const 0xd9 //217(0xEC,236 ��� 400��) //5 �� ��� 8 ��� ������� �� 8��� 200 ��, 2,5�� �� 16��� 400��
#define TCNTCC 57724 //0xe17c 1�� 1 ��� �� 16 ��� ������ �� 8 ���
//*
#define SB(port,bit) (PORT##port|=(1<<bit))		//setbit (port,bit) �������� ��� ����� ���� ���� ���� � ����� �����
#define CB(port,bit) (PORT##port&= ~(1<<bit))   //clearbit � ����� ������� �������� ���� � ��� ��� �������� ����
#define TB(port,bit) (PORT##port^=(1<<bit))		//togglebit � ��� , ���� �� ���� ������ PORTC  ���� ������ C � ���
#define CH(port,bit) (PIN##port&(1<<bit))		//checkbit CH(B,3) ��� ���� ��� ����� ���������
//*/
// ��� ��� ��������� , �� ��� �������� ��� ����� ����������� PIN ?
// � �� �������� ������� � ���� ������������� �� ������������

// ���� ����� ��� ����� C

#define SBC(x) (PORTC|=(1<<x))		//setbit
#define CBC(x)	(PORTC&= ~(1<<x))	//clearbit
#define TBC(x) (PORTC^=(1<<x))		//togglebit
#define CHC(x) (PINC&(1<<x))		//checkbit PIN  �� ���� , � �� PORT

/*/ ������� ��������� �� scmRTOS pin_macros.h  (AVR/avr-gcc)
#define PM_SETL(port,bit,dummy) (PORT##port &= ~(1<<(bit))) // ��� ��� � �������� ������ �����������
#define PM_SETH(port,bit,dummy) (PORT##port |= (1<<(bit)))  // ##
#define PM_SET(port,bit,val) PM_SET##val(port,bit,dummy)
#define ON(x) PM_SET(x)
#define SET(x) PM_SETH(x)
#define CLR(x) PM_SETL(x)
//*/

 // �������� ���������� ������� , ������� ����

/******************������********************----//��� ��� ���� �������� , ��� ������� ������ �������� � flags.KeyPin
#define KP1 (PINC&(1<<PC0))   //KP = Key Port � �� �� ��� �� ������� ��� �� ������ � ������ ������ ?
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
// � ������ ���� ������ ����� ���������
/*
typedef enum f {           // ����� �������� ���� Btn KeyCode � ����������� ��������� ��� int
    truba_btn=4,      //0 ��� ����� +1 ��� � ����� �� ��������
    fire_btn=2,       //1 ��� ������ ������� ���� ���������
    podacha_btn=1,    //2 ��� � ������� ������� ��
    avtomat_btn=5,    //3 ���� �� ��� ����� ����� ������� ����������
    count_btn=3;      //4
    //plus1_btn=6,      //5
    //plus2_btn=7       //6
};
//*/

/***********������ ������ ������*****************************************************
#define truba_btn (!(PINC&(1<<PC2)))&&(PINC&(1<<PC1))&&(PINC&(1<<PC0))          //100
#define fire_btn ((PINC&(1<<PC2)))&&(!(PINC&(1<<PC1)))&&(PINC&(1<<PC0))         //010
#define podacha_btn ((PINC&(1<<PC2)))&&((PINC&(1<<PC1)))&&(!(PINC&(1<<PC0)))    //001
#define avtomat_btn (!(PINC&(1<<PC2)))&&((PINC&(1<<PC1)))&&(!(PINC&(1<<PC0)))   //101
#define count_btn ((PINC&(1<<PC2)))&&(!(PINC&(1<<PC1)))&&(!(PINC&(1<<PC0)))     //011
///+********************************************************************************/
//#define truba_off CBC(5)//(PORTC&= ~(1<<PC5)) ������� ���� �������
//#define truba_on SBC(5)//(PORTC|=(1<<PC5))
#endif // MACROS_
///----------------------------------------------
///-----��� ��� ���������
///----------------------------------------------
/*
#define SB(port,bit) (PORT##port|=(1<<bit))		//setbit (port,bit)
#define CB(port,bit) (PORT##port&= ~(1<<bit))   //clearbit CH(B,3) ��� ���� ��� ����� ���������
#define TB(port,bit) (PORT##port^=(1<<bit))		//togglebit
#define CH(port,bit) (PIN##port&(1<<bit))		//checkbit
//*/
#include <stdbool.h>

#pragma once
//*
typedef struct { //��������� ���������� , ����� ������� �� ������ ���� �� ����� ?
  bool State_Automate:1;    //����������
  bool KeyPressed:1;        //���� ������� �������
  bool KeyReleased:1;       //���� ���������� �������
  bool KeyPushLong:1;       //���� ������� ������� �������
  bool KeyState:1;          //���� ��������� �������
  uint8_t  KeyPin:4;        //����� ��� �������
  bool Fire:1;            //���� �������
  bool Furnace:1;         //���� ����������� ����
  bool SupplyManual:1;
  bool SupplyAuto:1;          //���� ������
  bool ADC_Channel:1;      // ����� ���
  bool NextState:1;
  bool RunFlag:1;
 } PackedBool;
PackedBool flags;
int *KeyCodePointer;
//*/



