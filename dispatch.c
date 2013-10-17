#include "dispatch.h"

//TODO: ���������� ���������
//����� �������� ��������� ������������ ������� ����� ������� �� ��� ��� ������
// � ����� ��� ������ ���������� � �������...
void AddTask (void (*taskfunc)(void), u16 taskdelay, u16 taskperiod){
   u8 n=0;
   u8 position=0;
   while (((TaskArray[n].pfunc!=0)||(TaskArray[n].delay!=0))&&(TaskArray[n].delay<=((taskdelay==0)?(++taskdelay):(taskdelay))&&(n < MAXnTASKS)))n++;
    position=n;
   while ((TaskArray[n].pfunc != 0) && (TaskArray[n].delay!=0) && (n < MAXnTASKS))n++;
   for (/*.*/;n>position;n--){
        TaskArray[n]=TaskArray[n-1];
   }
        TaskArray[position].pfunc = taskfunc;
        TaskArray[position].delay = taskdelay;
        TaskArray[position].period = taskperiod;
        TaskArray[position].run = 0;
}


ISR(TIMER2_OVF_vect){
    timer2++;
   TCNT2 = StartFrom;
   if (flags.RunFlag==0)delay_time--;
   if (delay_time==0)flags.RunFlag=1;
}

void DispatchTask (void){
    uint8_t n=0;
    if (flags.RunFlag==1){                     // ���� ������ �������� ����
        task tmp;                       // ���������� ��� �������� �������� ��������
        tmp=TaskArray[0];
    while (((TaskArray[n].pfunc != 0) || (TaskArray[n].delay!=0)) && (n < MAXnTASKS)){
        n++;
        TaskArray[n-1]=TaskArray[n];
        if (TaskArray[n-1].delay) TaskArray[n-1].delay-=dt;
   }
    DeleteTask(n);
    if (tmp.period) {AddTask(*tmp.pfunc,tmp.period,tmp.period);}
    else AddTask(*tmp.pfunc,tmp.period,tmp.period);
    //TODO(geraki):����������� � ���������� ������� �������, ������ � ������� ���������, ��������� ��������� �� �����
    if (TaskArray[0].delay!=0) {delay_time=TaskArray[0].delay;} // ���� ����� +1 , �� ������� �������� ))))
    else {delay_time=1;} //����� ���� ������� �������� ���� , �� � ������� ����� ������ �������� � �-�� ��������
    dt=delay_time;      //��� �������� ���� �������� ���������� , ������ ��� ����� ����� ��� ��������
    (*tmp.pfunc)();
    flags.RunFlag=0;       //�� ������� ���-�� ����� ����������� ������� � ������� ���������� �������
   }
}

void DeleteTask (u8 j)
{
   TaskArray[j].pfunc = 0x0000;
   TaskArray[j].delay = 0;
   TaskArray[j].period = 0;
   TaskArray[j].run = 0;
}

void InitScheduler (void){
   u8 i;
   TCCR2 |= (1<<CS02)|(0<<CS01)|(1<<CS00);   // ������������� ��������� - 1024(101) 256(100) 64(011) 8(010) 0(001) off(000)
   TIFR = 1<<TOV0;   // ������� ���� ���������� ������� �0
   TIMSK |= 1<<TOIE2;   // ��������� ���������� �� ������������
   TCNT2 = StartFrom;    // ��������� ��������� ��. � ������� �������
   for (i=0; i<MAXnTASKS; i++) DeleteTask(i);   // ������� ������ �����
}
