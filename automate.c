#include "automate.h"
extern uint16_t timerFunction;
//TODO: переключатель по таймеру , обнуление счетчиков при остановке, блокировка ручного управления и наоборот

void StateAutomate(){
    flags.State_Automate=0;
    switch (KeyCurrentCode){
        case 0:// IND_OutputFormat(11, 7,  5,  3);
                break;
        case 1: IND_OutputFormatChar(" POD",0,1);
        //*
                if (flags.SupplyManual){
                    flags.SupplyManual=0;
                    CB(C,3);
                }else {
                    flags.SupplyManual=1;
                    SB(C,3);
                }
        //*/
                timer2=0;
                timerFunction=timer2+1;
                NextState=2;
                flags.NextState=1;
                timer2_works=1000;
                KeyCurrentCode=0;
                ;break;     //3 кнопка подачи
        case 2: IND_OutputFormatChar("_GOP",0,1);
                if (flags.Fire){
                    flags.Fire=0;
                    CB(C,4);
                }else {
                    flags.Fire=1;
                    SB(C,4);
                }
                KeyCurrentCode=0;
                break;     //4 кнопка горелки
        case 3: IND_OutputFormatChar("CTAP",0,1);
                if (!flags.SupplyAuto){
                    flags.SupplyAuto=1;
                    flags.SupplyManual=0;
                }else flags.SupplyAuto=0;
                KeyCurrentCode=0;
                break;     //1 кнопка старт/стоп счетчика
        case 4: IND_OutputFormatChar("TPUB",0,1);
                if (flags.Furnace){
                    flags.Furnace=0;
                    CB(C,5);
                }else {
                    flags.Furnace=1;
                    SB(C,5);
                }
                KeyCurrentCode=0;
                break;     //5 кнопка трубы
        case 5: IND_OutputFormatChar("AVTO",0,1);break;     //2 кнопка авто вкл/выкл
        case 6: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;     //----- не подключены кнопки
        case 7: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;     //-----
        case 8: IND_OutputFormat(55, 5,  5,  3);break;          //долгое нажатие нуля :)
        case 9: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;     // 3
        case 10: NextState=1;flags.NextState=1;IND_OutputFormatChar("ECT",0,1);break;                        //4
        case 11: IND_Time(3726,1);break;                        //1
        case 12: IND_OutputFormat(ascii2int('_'), 5,  1,  3);break;//5
        case 13: NextState=1;
                flags.NextState=1;
                IND_OutputFormatChar("ECT",0,1);
                timer2=0;
                timer2_works=500;
                timerFunction=timer2+1;
                break;    //2
        case 14: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;
        case 15: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    //------
        case 16: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    //
        case 17: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    //отсюда начнутся функции агрегата
        case 18: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    //долго конечно , но для начала хватит
        case 19: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    //
        case 20: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    //
        case 21: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    //
        case 22: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    //
        case 23: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    //
        case 24: IND_OutputFormat(KeyCurrentCode, 5,  5,  3);break;    //
        default:IND_OutputFormat(99, 7,  5,  3);break;
    }
}

//TODO: display handler , что показывать , сколько показывать , как показывать :)
void DisplayHandler(){
    switch(dispCode){
        case 0 : break;     // очистить
        case 1 : break;     // мигать
        case 2 : break;     // показать недолго
        case 3 : break;     // показывать долго
        case 4 : break;     // показвать , пока не произойдет какое либо событие
        default: break;
    }
}
