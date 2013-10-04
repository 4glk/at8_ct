
// ������� ������� , ������ � �������

#include "timer.h"


ISR( TIMER1_OVF_vect )  //�� ������������� � �������� ����� 1 ��� ^^
{
 // TCNT1 = TCNTCC; //���������� ��������� �������� TCNT1 (65536 � 1080) =  ��� 11��� 64456
	//(92.593 ��� 65536*92.593*10^-6 = 6.068 �������,  8-�� ������ �  0.0237 �������)
	//�������� ������� / ������������ (1024), 16bit=65536 ����� 8��� = 256 �����
	// 4000000/1024=3906 ~ 1/3906=256 msec * 65536 = 16.7 sec
	TCNT1=57724;
//	TCNT1=65500;
//    TCNT1=500;
//if (CH(C,5)) {CB(C,5);}else SB(C,5); // �������� �������
//    IND_Time(Time++,5);
//	 ������������� �� �������
//*
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
		}
			else{
			CurrentTime=adc7;
			TimeStop=CurrentTime+1;
			flags.ADC_Channel=0;
		}

	}

if (flags.ADC_Channel==0) {TimeStop--;}
	else {TimeSupply--;}
}
//*/
}
void InitTimer(){

  TIMSK = (1<<TOIE0)|(1<<TOIE1); // ������������
  TCCR0 = (1<<CS02)|(0<<CS01)|(1<<CS00); // ������������ 1024
  TCNT0 = TCNT0_const;

	//DDRD = ( 1 << PD7 );  // ����������� PC3 �� �����
	TCCR1B = (1<<CS12)|(0<<CS11)|(1<<CS10); // ����������� �������� 100=256 101=1024
//	TIMSK = (1<<TOIE1); // ��������� ���������� �� ������������ ������� 1 // ���������� � ������� ����
	TCNT1 = 57724;        // ���������� ��������� �������� TCNT1 64456 57724
	// � ���� ������ ��� 8��� 65536-7812=57724 8000000/1024=7812 ����� �� ���� �������
	//������� ������� � 57724
	//TCCR1B |= (1 << WGM12)|(0 << CS12)|(1 << CS12)|(0 << CS12); //8MHz/256/(1+31249)=1Hz
	//OCR1A = 31249;
	              // ���������� ��� ������ ���������� ����������
}

ISR(TIMER0_OVF_vect) // �� ������������ � �������� 10�� (10kHz)
{
  //  PackedBool flags;
  TCNT0 = TCNT0_const;  //7812   217  //8000000/1024
 // IND_Output(1234,3);
IND_Time(CurrentTime,5);
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
 //   if (CH(C,4)) {CB(C,4);}else SB(C,4);// �� ������������ � �������� 10��(100��)
}

