#include "dispatch.h"

//TODO: ���������� ���������
/*
int main(void){
    InitUART (UBRRvalue);   // �������������
    InitScheduler();
    AddTask (TestA, 0, 3);  // ���������� �����
    AddTask (TestB, 1, 4);
    AddTask (TestC, 4, 0);
//    AddTask (TestD, 20, 7);
//    AddTask (TestE, 15, 17);
//    AddTask (TestF, 17, 20);
//    AddTask (TestG, 12, 10);
//    AddTask (TestH, 10, 30);
//    AddTask (TestI, 200, 300);
    AddTask (Debug_osc_a,5,5);
    AddTask (Debug_osc_b,10,10);
    AddTask (Debug_osc_c,20,20);
    AddTask (Debug_osc_d,40,40);
//    AddTask (TestJ, 4, 0);
    PORTB=0b11111111;
    DDRB=0b11111111;
    sei();
    runFlag=TRUE;
 //      delay_time_ptr=&delay_time;
    while (1){
      DispatchTask();
    }
}
//*/
//����� �������� ��������� ������������ ������� ����� ������� �� ��� ��� ������
// � ����� ��� ������ ���������� � �������...
void AddTask (void (*taskfunc)(void), u16 taskdelay, u16 taskperiod){
   u8 n=0;
   u8 position=0;
   //���� ������� ��� ����� ������
   while (((TaskArray[n].pfunc!=0)||(TaskArray[n].delay!=0))&&(TaskArray[n].delay<=((taskdelay==0)?(++taskdelay):(taskdelay))&&(n < MAXnTASKS)))n++;
    position=n; // ������� ����� ������ ^^^^^^^^^^^^^^^^^^ ��� ������� ������ ����� �������� ������
    //������ ����� ���������� �������                // ����� �� ��������� � �������� � ������� ��������
    // ���� �����, ������ ������� ���� ���� ������� � �������� �� ����� ����
   while ((TaskArray[n].pfunc != 0) && (TaskArray[n].delay!=0) && (n < MAXnTASKS))n++;
   // ������ ������ �������� � ����� �� ��������� ������� ������
   for (/*.*/;n>position;n--){
        TaskArray[n]=TaskArray[n-1];
   }
         //������ ������ ����� ������ � ��������� �������
        TaskArray[position].pfunc = taskfunc;
        TaskArray[position].delay = taskdelay;
        TaskArray[position].period = taskperiod;
        TaskArray[position].run = 0;
}


ISR(TIMER2_OVF_vect){
//   u8 m;
    timer2++;
//   TransmitByte('-');           //DEBUG ������� �� ������� �������� , � �� �������� :)
   TCNT2 = StartFrom;
   //����������: ��� ������� � ���� �������
   if (flags.RunFlag==0)delay_time--;
   if (delay_time==0)flags.RunFlag=1;

}
//+ ��������������: ����� ���������� ������ �������� ������� �����, ������� ��������� ����� �� ���� �����
//+ �������� ���������� �������� � ���������� � ���� ����������
//+ ���������� �� ����� ���������� , ���� ������ � �������� , �� �������� �� ��� ����� � ���������
//+ ��������� � ���������� �������
// ���������� ������� ������ ������������ � ����������/��������� ������
void DispatchTask (void){
  // u8 k;
    uint8_t n=0;

    if (flags.RunFlag==1){                     // ���� ������ �������� ����

//        dt=delay_time;               // ����� �������� �������� , ��� �� ����������� � ����������
        task tmp;                       // ���������� ��� �������� �������� ��������
        tmp=TaskArray[0];
    //    (*TaskArray[0].pfunc)();     // ������ ������ � ������� ������
    //  ������ ������� � �������� ����� ���� ���� ������� � �������� �� ����� ����
    // ������ ���� ���� ������� ��� ���� ��������
    while (((TaskArray[n].pfunc != 0) || (TaskArray[n].delay!=0)) && (n < MAXnTASKS)){
        n++;
        TaskArray[n-1]=TaskArray[n];
        if (TaskArray[n-1].delay) TaskArray[n-1].delay-=dt;
   }
   //������� ��������� ������ � �������
    DeleteTask(n);
    //�������� ������������� ������
    if (tmp.period) {AddTask(*tmp.pfunc,tmp.period,tmp.period);} //���� �������� �������� +1 ��� ������� ��������
    else AddTask(*tmp.pfunc,tmp.period,tmp.period);
    //�������� ���� �������
    //TODO(geraki):����������� � ���������� ������� �������, ������ � ������� ���������, ��������� ��������� �� �����
    if (TaskArray[0].delay!=0) {delay_time=TaskArray[0].delay;} // ���� ����� +1 , �� ������� �������� ))))
    else {delay_time=1;} //����� ���� ������� �������� ���� , �� � ������� ����� ������ �������� � �-�� ��������
    dt=delay_time;      //��� �������� ���� �������� ���������� , ������ ��� ����� ����� ��� ��������
    (*tmp.pfunc)();
    flags.RunFlag=0;       //�� ������� ���-�� ����� ����������� ������� � ������� ���������� �������
    // ��������� ����� ������� � ������ ����� � ����������� ����� ����� ������������ �������� ����������
    //+ ������ � ������� ������ � ������� ��������� ����� ��������� � ������� , � �� ����� , ��������������� ��������
    //+ ����� �������� ������������ , ����� ��� ���������� � �������
   }
}

void DeleteTask (u8 j)
{
   TaskArray[j].pfunc = 0x0000;
   TaskArray[j].delay = 0;
   TaskArray[j].period = 0;
   TaskArray[j].run = 0;
}
#ifdef UART
void TestA (void){
   TransmitByte('A');
}

void TestB (void){
   TransmitByte('B');
}

void TestC (void){
   TransmitByte('C');
}

void TestD (void){
   TransmitByte('D');
}

void TestE (void){
   TransmitByte('E');
}

void TestF (void){
   TransmitByte('F');
}

void TestG (void){
   TransmitByte('G');
}

void TestH (void){
   TransmitByte('H');
}

void TestI (void){
   TransmitByte('I');
}
#endif
#ifdef OSC
// ����� ����� ������ �� �����������
void Debug_osc_a(void){
    TB(B,0);
}

void Debug_osc_b(void){
    TB(B,1);
}

void Debug_osc_c(void){
    TB(B,2);
}

void Debug_osc_d(void){
    TB(B,3);
}
#endif
#ifdef UART
void InitUART (u16 baud){ //0x0033
   UBRRH = (u8)(baud>>8);
   UBRRL = (u8)baud;
   UCSRB = (1<<RXEN)|(1<<TXEN);
   UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); //8bit 1stopbit
   sei();
}

void TransmitByte (u8 data){
   while ( !( UCSRA & (1<<UDRE)) );
   UDR = data;
}
#endif

void InitScheduler (void){
   u8 i;
   TCCR2 |= (1<<CS02)|(0<<CS01)|(1<<CS00);   // ������������� ��������� - 1024(101) 256(100) 64(011) 8(010) 0(001) off(000)
   TIFR = 1<<TOV0;   // ������� ���� ���������� ������� �0
   TIMSK |= 1<<TOIE2;   // ��������� ���������� �� ������������
   TCNT2 = StartFrom;    // ��������� ��������� ��. � ������� �������
   for (i=0; i<MAXnTASKS; i++) DeleteTask(i);   // ������� ������ �����
}
