#include "kbd.h"
//extern void AddTask (void (*taskfunc)(void), u16 taskdelay, u16 taskperiod);
//  ���������� �������
/*
int trigger(int btn,int port){
			//   *
			if (btn&&(!(CH(C,port)))) {
			delay(250);
			if (btn&&(!(CH(C,port))))
				SBC(port);
				//{SBC(port);while ((btn)){if((!btn))break;};}
			delay(750);
				return 0;
			}
			// ���������
			if ((CH(C,port))&&btn) {
			delay(250);
			if ((CH(C,port))&&btn)
				(CB(C,port));
				//{(CB(C,port));while ((btn)){if((!btn))break;};}
			delay(750);
			return 0;
			}
			return 0;

}
//*/
//#include "kbd.h"
//*
void InitControl(){
	DDRC=0b00111000;
	//DDRA |= (1 << PC1)|(1 << PC2)|(1 << PC3)|(1 << PC4)|(1 << PC5)|(1 << PC6);
	PORTC=0b00000111;
}
//*/
//*
uint8_t KeyCode(){

    return (flags.KeyPin);
    }
//*/
void KeyState(){

    if (((flags.KeyPressed)&&(flags.KeyReleased))||((flags.KeyPressed)&&(flags.KeyPushLong))){
        flags.KeyPressed=0;
        if (flags.KeyPushLong){
            flags.KeyPin+=8;
            //flags.KeyPushLong=0;
        }
        flags.KeyPushLong=0;
        flags.State_Automate=1;
    }
    flags.KeyReleased=1;
    KeyCurrentCode=flags.KeyPin;
  //  flags.State_Automate=1;
 //   AddTask(StateAutomate,5,0);
 //   *KeyCodePointer = &KeyCurrentCode;
}

void KeyScan(){
  if(~PINC&0b00000111){ // ���������� �������
    flags.KeyReleased=0;
        if (++i > 5 ) {      //�������� ������� 100-250 �����������
            if (!flags.KeyPressed){flags.KeyPressed = 1;flags.KeyPin=(~PINC&0b00000111);}
               if ( i > 100 ){  //������� ������� 1-3 �������
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
        AddTask(KeyScan,25);
}
