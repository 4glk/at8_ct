/***������-����������***/
// TODO: ���� �����
//+ ����������� � ��������� ������� ����� , ������ ����� ������ � ������������� ���������� ���������� i ��� z , ������ ����
//+ � ������������� ���������� ������� � ������������ ������� avr-gcc
//- �������� ��������� ����� �� ������� , ������������ ������ ������ � ������������ ������ �������� , � �������������
//- ���������� �������� � ��������� 74hc164 ��� 74hc595
//- ������ � ��������� ����� ����� ��������� , ������ ��� �� ��������
//- ������ ������� ������� ����������� ��������� �������� �������� , ���������� � ��� ������ ������������
//- ������������ ������ �� �������� , � ��������� ������� ������ (class string) , ������ � ������������
//- ����������� � ������������� ������ , ���������� ������� � ������ ������ , ������� , � ����� ������ ������� ��� ��������� ������
//- ���������� ��� , ����� ������ ������ �������������� �� ���� � ������� , ������� �������������� �� 10
//- ����������� ���� ������� , �������� � ������ � ����
//- event-system !!!!
//- state (���������)-> event (�������) -> state (���������) -> handler(����������)
//- event-sources[1..x] -> loop order (��������� �������) -> dipatcher -> handlers

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>
#include "macros.h"     //�������� ������ � ������ � ������
#include "kbd.h"        //������ � �����������
#include "adc.h"
#include "indicator.h"
#include "spi.h"
#include "automate.h"
#include "timer.h"
#include "compilers.h"




//////////////   *******************���������� , ��������� ���������� ���������� , �������� ����� ���������
/*
volatile int adc_but,BUTTON;
volatile int adc6,adc7;
volatile int ch_st=0; // 0 - 1 channel, 1 - 2 channel
volatile int counti=0,count1=0,count2=0;
int adc6_a=0,adc7_a=0; //���������� ��� ����������� ������������� �������
volatile unsigned char segcounter = 0;
volatile int display1 = 0;
volatile int display2 = 0;
int count_st=0;
int z=10,i=0; // �� �������� ��������� ��� ���������� ��������

///////////////    **************�������
//void delay(int x);				//������� ��������
int trigger(int btn,int port);	//������� ������������

//*/

uint16_t i;
/***������� �������***/
int main (void)
{

 //   TCNT1 = 57724;
 //   flags.KeyPressed=0;
//	InitDisplay();
	InitTimer();
//	InitADC();
//	InitControl();
	//TODO: ���������� ���������� ������� (���� ����� �������� ������� � ������������)

	  //������������� ���������� � ���
  IND_Init();
//  ADC_Init();
  InitControl();
  //PackedBool flags;

  //������������� ������� �0
  TIMSK = (1<<TOIE0)|(1<<TOIE1); // ������������
  TCCR0 = (1<<CS02)|(0<<CS01)|(1<<CS00); // ������������ 1024
  TCNT0 = TCNT0_const;
    flags.KeyPin=0;
    flags.KeyPushLong=0;
    flags.KeyState=0;
    flags.KeyPressed = 0;
    flags.KeyReleased = 1;
    flags.State_Automate=0;
 //   DDRC=0b00111000;
  sei();
while(1){
   // IND_Output(23332,0);
    //IND_OutputFormatChar("HEFH",1,1);
    //IND_OutputFormatChar("ABCD",6,4);
   // IND_OutputFormat(12345678, 1,  1,  8);
    if (flags.State_Automate)StateAutomate(KeyCode());
        /* // ���������� ���������� , ���������
	display1=count1; if (display1==0) {display1=adc6_a;delay(2000);} //����������� �������� ,
	display2=count2; if (display2==0) {display2=adc7_a;delay(2000);} //���� 0 �� �������� ������������ ��������
	if (adc6_a!=adc6) {display1=adc6;delay(2000);adc6_a=adc6;}      //���� ������ ����� , �� �������� ��� ��������
	if (adc7_a!=adc7) {display2=adc7;delay(2000);adc7_a=adc7;}       // ��� ��� ����� ���� ������� � ���������� ���������
	/////////    ***********������� ����� ���� , ������� ������ (���� � ���� ������ ���� ���)**********
	// ��� ��� ������������ , ������� ����� ����� ����� ������ ������ ��� �����������
	if (count_btn&&(count_st==0)){delay(150);if (count_btn&&(count_st==0));count_st=1;delay(750);}
	if (count_btn&&(count_st==1)){delay(150);if (count_btn&&(count_st==1));count_st=0;CBC(3);counti=0;delay(750);} //��������� �������
	if (podacha_btn&&(count_st==0)) {trigger(podacha_btn,3);}
	//  *
	if ((ch_st==1)&&(count_st==1)){PORTC|=(1<<PC3);}
	if ((ch_st==0)&&(count_st==1)){PORTC&= ~(1<<PC3);}
	//    *
	//////    ***********************����� ������������� �_� ***********
	if (truba_btn){trigger(truba_btn,5);}
	//////////   *********�������************
	if (fire_btn){trigger(fire_btn,4);} //1

	//*/

}return 0;
}

ISR(TIMER0_OVF_vect) // �� ������������ � �������� 10�� (10kHz)
{
  //  PackedBool flags;
  TCNT0 = TCNT0_const;  //7812   217  //8000000/1024
 // IND_Output(1234,3);
  IND_Update();
 // if(1){
  if(~PINC&0b00000111){ // ���������� �������
    flags.KeyReleased=0;
        if (++i > 25 ) {      //�������� ������� 100 �����������
            if (!flags.KeyPressed){flags.KeyPressed = 1;flags.KeyPin=(~PINC&0b00000111);}
               if ( i >100 ){  //������� ������� 3 �������
                 if (!flags.KeyPushLong){

                    flags.KeyPushLong=1;
                    KeyState();
                 }
               }
        }
    }
    else {
        i=0;
        if (!flags.KeyReleased) {flags.KeyReleased=1;}
        KeyState();
    }
    if (CH(C,4)) {CB(C,4);}else SB(C,4);// �� ������������ � �������� 10��(100��)
}
