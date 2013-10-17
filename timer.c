
// ������� ������� , ������ � �������

#include "timer.h"


ISR( TIMER1_OVF_vect )  //�� ������������� � �������� ����� 1 ��� ^^
{
	TCNT1=57724;
//TODO: ����������� � ����������� ������� , ������� ��� ���� ������ , ����� ��������� ����� � ��� �������� ,
// � ����� ������ �����������
if (flags.SupplyAuto==1){
if (CurrentTime!=0){
		CurrentTime--;
	}
	else{
		if (flags.ADC_Channel==0){
			CurrentTime=adc6;
			TimeSupply=CurrentTime+1;
			flags.ADC_Channel=1;
			SB(C,3);
		}
			else{
			CurrentTime=adc7;
			TimeStop=CurrentTime+1;
			flags.ADC_Channel=0;
			CB(C,3);
		}

	}

if (flags.ADC_Channel==0) {TimeStop--;}
	else {TimeSupply--;}
}
//*/
}
void InitTimer(){

  TIMSK = (1<<TOIE0)|(1<<TOIE1)|(1<<TOIE2); // ������������
  TCCR0 = (1<<CS02)|(0<<CS01)|(1<<CS00); // ������������ 1024
  TCNT0 = TCNT0_const;
  TCCR2 = (1<<CS02)|(0<<CS01)|(1<<CS00);
	TCCR1B = (1<<CS12)|(0<<CS11)|(1<<CS10); // ����������� �������� 100=256 101=1024
//	TIMSK = (1<<TOIE1); // ��������� ���������� �� ������������ ������� 1 // ���������� � ������� ����
	TCNT1 = 57724;        // ���������� ��������� �������� TCNT1 64456 57724
}

ISR(TIMER0_OVF_vect) // �� ������������ � �������� 10�� (10kHz)
{
  TCNT0 = TCNT0_const;  //7812   217  //8000000/1024
    (CH(C,4))?CB(C,4):SB(C,4);// �� ������������ � �������� 10��(100��),������ ������ ��
}
