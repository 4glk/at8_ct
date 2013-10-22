#include "automate.h"
extern uint16_t timerFunction;
//TODO: ������������� �� ������� , ��������� ��������� ��� ���������, ���������� ������� ���������� � ��������
//TODO: ������� ���� �� ������� ������� , ���� �� ��������� ����� ���� ������� ������� :)
void StateAutomate(){

    if (flags.State_Automate==1){
                flags.State_Automate=0;
    switch (KeyCurrentCode){
        case 0:break;
        case 1: ResetTask(FuncINDTime);
                AddTask(Supply_sw,AddCurrentTime,100,2000,0);break;     //3 ������ ������
        case 2: ResetTask(FuncINDTime);
                AddTask(Fire_sw,AddCurrentTime,100,2000,0); break;     //4 ������ �������
        case 3: //ResetTask(FuncINDTime);
                AddTask(Timer_sw,Idle,100,0,0);
                break;     //1 ������ �����/���� ��������
        case 4: ResetTask(FuncINDTime);
                AddTask(Furnance_sw,AddCurrentTime,100,2000,0);break;     //5 ������ �����
        case 5: //ResetTask(FuncINDTime);
                IND_OutputFormatChar("AVTO",0,1);
                break;     //2 ������ ���� ���/����
//        case 6: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;     //----- �� ���������� ������
//        case 7: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;     //-----
 //       case 8: IND_OutputFormat(55, 5,  5,  3);break;          //������ ������� ���� :)
        case 9: ResetTask(FuncINDTime);break;     // 3
        case 10: IND_OutputFormatChar("ECT",0,0);break;                        //4
        case 11: AddTask(Furnance_sw,Idle,250,0,0) ;break;                        //1
        case 12: AddTask(FuncINDOutput,Idle,250,0,1000);break;//5
        case 13: NextState=1;
                flags.NextState=1;
                IND_OutputFormatChar("ECT",0,1);
                timer2=0;
                timer2_works=500;
                timerFunction=timer2+1;
                break;    //2
//        case 14: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    // �� ���������� ������
//        case 15: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    //------
//        case 16: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    //
        default:break;
    }
    }

}

void Timer_sw(){
                IND_OutputFormatChar("CTAP",0,1);
                if (!flags.SupplyAuto){
                    flags.SupplyAuto=1;
                    flags.SupplyManual=0;
                }else flags.SupplyAuto=0;
                KeyCurrentCode=0;
}

void Supply_sw(){
            IND_OutputFormatChar(" POD",0,1);
        //*
                if (CH(C,3)){
                 //   flags.SupplyManual=0;
                    CB(C,3);
                }else {
                //    flags.SupplyManual=1;
                    SB(C,3);
                }
        //*/
                timer2=0;
                timerFunction=timer2+1;
                NextState=2;
          //      flags.NextState=1;
                timer2_works=1000;
         //       KeyCurrentCode=0;

}

void AddCurrentTime(){
    AddTask(FuncINDTime,Idle,250,0,0xffff);
}

void FuncINDTime(){
    IND_Time(CurrentTime,5);
}

void FuncINDOutput(){
    IND_Output(1234,1);
}

void ToggleSupplyManual(){
    TB(C,3);
}

//*
void Idle(){

}
//*/


void Furnance_sw(){
                IND_OutputFormatChar("TPUB",0,1);
                if (CH(C,5)){
          //          flags.Furnace=0;
                    CB(C,5);
                }else {
          //          flags.Furnace=1;
                    SB(C,5);
                }
                KeyCurrentCode=0;
}

void Fire_sw(){
            IND_OutputFormatChar("_GOP",0,1);
                if (CH(C,4)){
            //        flags.Fire=0;
                    CB(C,4);
                }else {
            //        flags.Fire=1;
                    SB(C,4);
                }
                KeyCurrentCode=0;
}

//TODO: display handler , ��� ���������� , ������� ���������� , ��� ���������� :)
//������ ��������� ���������� �� ��
// � ������� ����������� ����� �� �� ��
/*
void DisplayHandler(){
    switch(dispCode){
        case 0 : break;     // ��������
        case 1 : break;     // ������
        case 2 : break;     // �������� �������
        case 3 : break;     // ���������� �����
        case 4 : break;     // ��������� , ���� �� ���������� ����� ���� �������
        default: break;
    }
}
//*/
