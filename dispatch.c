#include "dispatch.h"

//TODO: ���������� ���������
// ���� ����� ������� ��� ���� �������� �� �����
// ����� �������� ��������� ������������ ������� ����� ������� �� ��� ��� ������
// � ����� ��� ������ ���������� � �������...
// � ������ ���� �������� �������� ����� ������� ������� , ������� �� ���������� ������� ������ ������� ��� ��� �� ���
// ������ ������� ��� ���� �������� �� ������ ������� , ��������� ������� ��������� , �� ���� ��� ���� ����� � ����������
//             || || || || || || ||
//             \/ \/ \/ \/ \/ \/ \/
void AddTask (void (*taskfunc)(void),void (*nextfunc)(void), uint16_t taskdelay,uint16_t nextdelay,u16 taskruns){
   u8 n=0;
   u8 position=0;
   while (((TaskArray[n].pfunc!=0)||(TaskArray[n].delay!=0))&&(TaskArray[n].delay<=((taskdelay==0)?(++taskdelay):(taskdelay))&&(n < MAXnTASKS)))n++;
    position=n;
//    while ((((TaskArray[n].pfunc!=(taskfunc))&&(TaskArray[n].pfunc!=0))||(TaskArray[n].delay!=0))&&(TaskArray[n].delay<=((taskdelay==0)?(++taskdelay):(taskdelay))&&(n < MAXnTASKS)))n++;
//    position=n;


   while ((TaskArray[n].pfunc != 0) && (TaskArray[n].delay!=0) && (n < MAXnTASKS))n++;
   for (/*.*/;n>position;n--){
        TaskArray[n]=TaskArray[n-1];
   }
  //      if ((TaskArray[position].pfunc==(taskfunc))){// ���� ���� ��� ����� ������� � ������ , �� ��������� �� �����
 //       TaskArray[position].pfunc = taskfunc;
  //      TaskArray[position].delay += taskdelay;
  //      TaskArray[position].nextdelay = nextdelay;  // ���� �� ����� , ��� ������������� � ��������
 //       TaskArray[position].run = 0;
 //       TaskArray[position].numRun = taskruns;
  //      TaskArray[position].nextfunc = nextfunc; //  �������� ��������� �-�� � ����������� ���������� :(

  //      }else {
        TaskArray[position].pfunc = taskfunc;
        TaskArray[position].delay = taskdelay;
        TaskArray[position].nextdelay = nextdelay;  // ���� �� ����� , ��� ������������� � ��������
        TaskArray[position].run = 0;
        TaskArray[position].numRun = taskruns;
        TaskArray[position].nextfunc = nextfunc; //  �������� ��������� �-�� � ����������� ���������� :(
  //      }
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
        n++; //������ ���� ������� �� ������ �� ������ � ������ ���������
        TaskArray[n-1]=TaskArray[n];        //�������� ������� ������
        if (TaskArray[n-1].delay) TaskArray[n-1].delay-=dt;     //�������� ��������� ����� �� ������ ������
   }
    DeleteTask(n);      //������� ��������� ������
    // ���������� ������
    // 1. ���������� ��������� ������ task delay
    // 2. ���������� ���������� �������� ��������� ������ numRun
    // 3. ���������� ������������� ������ task period
    // ���� ������ ����� 0 , �� ��� ��������� ������ , ���� ����. �-�� ��� , �� �� ������� � �������.
    // ���� ������ ���� , �� ��� ����������� ������
    // ���� ������ �������� , �� ������ ��� ���������� �������� , ��������� ��� � ������ ��������
    // ����� ������ ����� � ��� , ��� ������ ����� �������� ���������� �������� ��� ��������
    // ������ ����� ������� ���������
    switch (tmp.numRun){
            case 0: if (*tmp.nextfunc!=Idle) AddTask(*tmp.nextfunc,Idle,tmp.nextdelay,0,tmp.numRun);break;
            case 0xffff: AddTask(*tmp.pfunc,*tmp.nextfunc,tmp.delay,tmp.nextdelay,tmp.numRun);break;
            default: if (tmp.numRun&&tmp.numRun!=0xffff) AddTask(*tmp.pfunc,*tmp.nextfunc,tmp.delay,tmp.nextdelay,--tmp.numRun);break;
    }
  //  if (tmp.period==0&&tmp.numRun==0) {AddTask(*tmp.pfunc,*tmp.nextfunc,tmp.delay,tmp.period,tmp.numRun);}
   // if (tmp.period&&tmp.numRun==0) {AddTask(*tmp.pfunc,*tmp.nextfunc,tmp.period,tmp.period,tmp.numRun);}
   // if (tmp.period&&tmp.numRun!=0) {AddTask(*tmp.pfunc,*tmp.nextfunc,tmp.period,tmp.period,--tmp.numRun);}
  //  else AddTask(*tmp.pfunc,tmp.period,tmp.period);
    //TODO:����������� � ���������� ������� �������, ������ � ������� ���������, ��������� ��������� �� �����
    if (TaskArray[0].delay!=0) {delay_time=TaskArray[0].delay;} // ���� ����� +1 , �� ������� �������� ))))
    else {delay_time=1;} //����� ���� ������� �������� ���� , �� � ������� ����� ������ �������� � �-�� ��������
    dt=delay_time;      //��� �������� ���� �������� ���������� , ������ ��� ����� ����� ��� ��������
    (*tmp.pfunc)();
    flags.RunFlag=0;       //�� ������� ���-�� ����� ����������� ������� � ������� ���������� �������
   }
}

void ResetTask(void (*resfunc)(void)){
//    task tmp;
    int i=0;
    while (TaskArray[i].pfunc!=*resfunc)i++;
    TaskArray[i].numRun=0;
}

void DeleteTask (u8 j)
{
   TaskArray[j].pfunc = 0x0000;
   TaskArray[j].delay = 0;
//   TaskArray[j].period = 0;
   TaskArray[j].run = 0;
   TaskArray[j].nextfunc = 0x0000;
   TaskArray[j].numRun =0;
   TaskArray[j].nextdelay=0;
}

void InitScheduler (void){
   u8 i;
   TCCR2 |= (1<<CS02)|(0<<CS01)|(0<<CS00);   // ������������� ��������� - 1024(101) 256(100) 64(011) 8(010) 0(001) off(000)
   TIFR = 1<<TOV0;   // ������� ���� ���������� ������� �0
   TIMSK |= 1<<TOIE2;   // ��������� ���������� �� ������������
   TCNT2 = StartFrom;    // ��������� ��������� ��. � ������� �������
   for (i=0; i<MAXnTASKS; i++) DeleteTask(i);   // ������� ������ �����
}
