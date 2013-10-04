#include "automate.h"


void StateAutomate(KeyCode){
   // PackedBool flags;
    flags.State_Automate=0;
  //*
    switch (KeyCode){
        case 0: IND_OutputFormat(11, 7,  5,  3);break;
        case 1: IND_OutputFormat(ascii2int('A'), 5,  5,  3);break;     //3 кнопка
        case 2: IND_Time(65,1);break;     //4
        case 3: IND_OutputFormatChar("HF",1,1);break;     //1
        case 4: IND_OutputFormatChar("EDA HADA", 1,1);break;     //5
        case 5: IND_OutputFormatChar("DEFH",1,3);break;     //2
        case 6: IND_OutputFormat(KeyCode, 5,  5,  3);break;     //-----
        case 7: IND_OutputFormat(KeyCode, 5,  5,  3);break;     //-----
        case 8: IND_OutputFormat(55, 5,  5,  3);break;          //долгое нажатие нуля :)
        case 9: IND_OutputFormat(KeyCode, 5,  5,  3);break;
        case 10: IND_Time(4725,5);break;
        case 11: IND_Time(3726,5);break;
        case 12: IND_OutputFormat(KeyCode, 5,  5,  3);break;
        case 13: IND_OutputFormat(KeyCode, 5,  5,  3);break;
        case 14: IND_OutputFormat(KeyCode, 5,  5,  3);break;    //------
        case 15: IND_OutputFormat(KeyCode, 5,  5,  3);break;    //------
        default:IND_OutputFormat(99, 7,  5,  3);break;
    }
    //*/
}
