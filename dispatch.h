#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "macros.h"

/// ���� ������ //
typedef unsigned char u8;
typedef unsigned int u16;
typedef struct task{
   void (*pfunc) (void);    // ��������� �� �������
   u16 delay;               // �������� ����� ������ �������� ������
   u16 period;              // ������ ������� ������
   u8 run;                  // ���� ���������� ������ � �������
}task;                      // ���� ������� ����� ������� �� ���������

//typedef enum boolean{FALSE,TRUE}boolean;
//bool runFlag=FALSE;
//uint16_t *delay_time_ptr;
uint16_t delay_time;
        uint16_t dt;
extern uint16_t timer2;

/// ����������� ///////////
// ��������� ��� ������� �0
// 25 �� ��� �������� �������
// 8 ��� � ������������ 1024
//#define StartFrom       0x3D //��� 25 �� 40��
#define StartFrom       0xF8 //��� 1 �� 1���            //�� ������� ������� ����� � ��� ��������
//#define StartFrom       0xB2 //��� 10 �� 100��        //������������ ��� ���������
// ������������ ���������� �����
#define MAXnTASKS       8
//��������� ��� UART`a
//�������� ������ 9600 ��� ������� 8 ���
#define UBRRvalue 0x0033
//#define UART
//#define OSC

/// ������ ����� ///////////
volatile task TaskArray[MAXnTASKS];

/// ��������� ������� ////////
#ifdef UART
void InitUART (u16 baud);       //������������� �����
void TransmitByte (u8 data);    //�������� ����� �� �����
#endif
void InitScheduler (void);      //������������� ����������
void UpdateScheduler(void);     //���������� ����������
void DeleteTask (u8 index);     //�������� ������
//TODO:����� ������� ��� ������� ����� ��������� �� ������� � ������ ����������� � ��� ���
void AddTask (void (*taskfunc)(void), u16 taskdelay, u16 taskperiod);   //���������� ������
void DispatchTask (void);       //������ ��� ��������� � ������ ������ �� �����
#ifdef UART
void TestA (void);
void TestB (void);
//void TestC (void);
//void TestD (void);
//void TestE (void);
//void TestF (void);
//void TestG (void);
//void TestH (void);
//void TestI (void);
#endif // UART
#ifdef OSC
void Debug_osc_a(void);
//void Debug_osc_b(void);
//void Debug_osc_c(void);
//void Debug_osc_d(void);
#endif
