#include "automate.h"

//TODO: ������������� �� ������� , ��������� ��������� ��� ���������, ���������� ������� ���������� � ��������
//TODO: ������� ���� �� ������� ������� , ���� �� ��������� ����� ���� ������� ������� :)
void StateAutomate(){

    if (flags.State_Automate==1){
                flags.State_Automate=0;
    switch (KeyCurrentCode){
        case 0:break;
        case 1: //ResetTask(FuncINDTime);
                AddTask(Supply_sw,100);break;     //3 ������ ������
        case 2:// ResetTask(FuncINDTime);
                AddTask(Fire_sw,100); break;     //4 ������ �������
        case 3: //ResetTask(FuncINDTime);
                AddTask(Timer_sw,100);
                break;     //1 ������ �����/���� ��������
        case 4: //ResetTask(FuncINDTime);
                AddTask(Furnance_sw,100);break;     //5 ������ �����
        case 5: //ResetTask(FuncINDTime);
                IND_OutputFormatChar("AVTO",0,1);
                break;     //2 ������ ���� ���/����
//        case 6: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;     //----- �� ���������� ������
//        case 7: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;     //-----
 //       case 8: IND_OutputFormat(55, 5,  5,  3);break;          //������ ������� ���� :)
        case 9: //ResetTask(FuncINDTime);
                break;     // 3
        case 10: IND_OutputFormatChar("ECT",0,0);break;                        //4
        case 11: AddTask(Furnance_sw,250) ;break;                        //1
        case 12: break;//5
        case 13: //NextState=1;
                //flags.NextState=1;
                //IND_OutputFormatChar("ECT",0,1);
                //timer2=0;
                //timer2_works=500;
                //timerFunction=timer2+1;
                break;    //2
//        case 14: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    // �� ���������� ������
//        case 15: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    //------
//        case 16: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    //
        default:break;
    }
    }
    AddTask(StateAutomate,50);
}

void Timer_sw(){    // ��� ������� ��������� �������� �� ������ � �������� ������� ���� ���������
                    AddTask(FuncINDTime,1500);
                IND_OutputFormatChar("CTAP",0,1);
                if (!flags.SupplyAuto){
                    flags.SupplyAuto=1;
                    flags.SupplyManual=0;
                }else {
                    flags.SupplyAuto=0;
                    CB(C,3);
                  //  TimeStop=adc6;
                  //  TimeSupply=adc7;
                }
                KeyCurrentCode=0;
}

void Supply_sw(){
             AddTask(FuncINDTime,1500);
            IND_OutputFormatChar(" POD",0,1);
            if (flags.SupplyAuto==1){
              flags.SupplyAuto=0;
              //  TimeSupply=0;
              //  TimeStop=0;
            }
        //*
                if (CH(C,3)){
                 //   flags.SupplyManual=0;
                    CB(C,3);
                }else {
                //    flags.SupplyManual=1;
                    SB(C,3);
                }
        //*/
}


void FuncINDTime(){
    IND_Time(TimeSupply,5);
    IND_Time(TimeStop,1);
    AddTask(FuncINDTime,250);
}

//*
void Idle(){

}
//*/


void Furnance_sw(){
           AddTask(FuncINDTime,1500);
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
         AddTask(FuncINDTime,1500);
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

void ShowAdc6(){
    AddTask(FuncINDTime,1000);
    IND_Time(adc6,5);

//    IND_Time(adc7,1);
}

void ShowAdc7(){
 //   IND_Time(adc6,5);
         AddTask(FuncINDTime,1000);
    IND_Time(adc7,1);

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
