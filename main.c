/***������-����������***/

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>       //���
#include "macros.h"     //�������� ������ � ������ � ������
#include "kbd.h"        //������ � �����������
#include "adc.h"        //������ � ���
#include "indicator.h"  // ������ � �����������������
#include "spi.h"        // ���������������� ���������
#include "automate.h"   // ���� ��������� �������� , ����� �������� ����� �� �����
#include "timer.h"      // ���� ��������
#include "compilers.h"  //�������� ������� ��������� , � ��������� ������ ��� ������ �����������
#include "sheduler/dispatch.h"   //���������
//TODO: �������� ����� ������ ������ �������� �� � �������� �������
//+���
//������
//+���������
//+������
//������� ��������

//TODO: ���������� ���� ��� ���������� �������
uint16_t TimeStop=0;
uint16_t TimeSupply=0;
uint16_t CurrentTime=0;
int KeyCurrentCode;
extern void doubleCountdown();
//template <typename AnyType>;
//const AnyType Sum(const AnyType &a, const AnyType &b,const AnyType &c)
//{
//  return a + b + c ;
//}
//������� :(
//extern void FuncINDTime();
/***������� �������***/
int main (void)
{
	InitTimer();
	InitADC();
    InitScheduler();
    IND_Init();
    InitControl();
  // ����� ����� ��� ��������� �������� , ����� ��� ����� �� ����� ��� �� ���
    flags.KeyPin=0;
    flags.KeyPushLong=0;
    flags.KeyState=0;
    flags.KeyPressed = 0;
    flags.KeyReleased = 1;
    flags.State_Automate=0;
    flags.SupplyAuto=0;
    flags.SupplyManual=0;
    flags.Furnace=0;        //(C,5)
    flags.NextState=0;
    flags.RunFlag=1;
    flags.TimerFlag=0;
    AddTask(IND_Update,10);
    AddTask(KeyScan,25);
    AddTask(FuncINDTime,250);
    AddTask(StateAutomate,50);
    AddTask(doubleCountdown,100);
    sei();
    while(1){
  /*//������� ������� �������������� ������������ �� ����� ������������ �������
        if (!(TIFR&(1<<TOV1))){
            AddTask(doubleCountdown,5);
           // (TIFR |= (1<<TOV1));
         //   (TIFR&= ~(1<<TOV1));
        }   //*/
        DispatchTask();

    }return 0;
}
