#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t adc6,adc7;//������ � ������� ���
void InitADC();
void AdcTaking();
void AdcMean();
extern void ShowAdc6();
extern void ShowAdc7();
uint16_t adc_buf;
uint16_t adc_result;
//uint8_t counti = 0;
extern void AddTask(void (*taskfunc)(void),void (*nextfunc)(void),uint16_t taskdelay,uint16_t nextdelay,uint16_t taskruns);
extern void Idle();
extern void FuncINDTime();
extern void ResetTask();
