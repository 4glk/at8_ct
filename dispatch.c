#include "dispatch.h"

//TODO: прикрутить диспетчер
/*
int main(void){
    InitUART (UBRRvalue);   // Инициализация
    InitScheduler();
    AddTask (TestA, 0, 3);  // Добавление задач
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
//чтобы передать параметры передаваемой функции нужно указать их тип для начала
// а потом уже мутить перегрузку и шаблоны...
void AddTask (void (*taskfunc)(void), u16 taskdelay, u16 taskperiod){
   u8 n=0;
   u8 position=0;
   //ищем позицию для новой задачи
   while (((TaskArray[n].pfunc!=0)||(TaskArray[n].delay!=0))&&(TaskArray[n].delay<=((taskdelay==0)?(++taskdelay):(taskdelay))&&(n < MAXnTASKS)))n++;
    position=n; // позиция новой задачи ^^^^^^^^^^^^^^^^^^ это условие скорее всего придется убрать
    //теперь нужно раздвинуть очередь                // чтобы не циклиться в функциях с нулевым периодом
    // ищем конец, крутим счетчик пока есть функция и задержка не равна нулю
   while ((TaskArray[n].pfunc != 0) && (TaskArray[n].delay!=0) && (n < MAXnTASKS))n++;
   // теперь собсна сдвигаем с конца до найденной позиции вправо
   for (/*.*/;n>position;n--){
        TaskArray[n]=TaskArray[n-1];
   }
         //собсна ставим новую задачу в найденную позицию
        TaskArray[position].pfunc = taskfunc;
        TaskArray[position].delay = taskdelay;
        TaskArray[position].period = taskperiod;
        TaskArray[position].run = 0;
}


ISR(TIMER2_OVF_vect){
//   u8 m;
    timer2++;
//   TransmitByte('-');           //DEBUG убирать на высоких частотах , а то заклинит :)
   TCNT2 = StartFrom;
   //переменные: сам счетчик и флаг запуска
   if (flags.RunFlag==0)delay_time--;
   if (delay_time==0)flags.RunFlag=1;

}
//+ модифицировать: после выполнения задачи сдвинуть очередь влево, вычесть прошедшее время из всех задач
//+ обнулить переменную счетчика в прерывании и флаг выполнения
//+ выполнение по флагу прерывания , если задача с периодом , то добавить ее как новую с задержкой
//+ указанной в переменной периода
// желательно сделать массив динамическим с выделением/удалением памяти
void DispatchTask (void){
  // u8 k;
    uint8_t n=0;

    if (flags.RunFlag==1){                     // если таймер выставил флаг

//        dt=delay_time;               // берем значение счетчика , шоб не перескочило в сортировке
        task tmp;                       // переменная для хранения нулевого элемента
        tmp=TaskArray[0];
    //    (*TaskArray[0].pfunc)();     // запуск первой в очереди задачи
    //  крутим счетчик и сдвигаем влево пока есть функция и задержка не равна нулю
    // запуск если есть функция или есть задержка
    while (((TaskArray[n].pfunc != 0) || (TaskArray[n].delay!=0)) && (n < MAXnTASKS)){
        n++;
        TaskArray[n-1]=TaskArray[n];
        if (TaskArray[n-1].delay) TaskArray[n-1].delay-=dt;
   }
   //удаляем последнюю задачу в массиве
    DeleteTask(n);
    //добавить переодическую задачу
    if (tmp.period) {AddTask(*tmp.pfunc,tmp.period,tmp.period);} //сюда допустим добавить +1 для нулевых задержек
    else AddTask(*tmp.pfunc,tmp.period,tmp.period);
    //обнуляем флаг запуска
    //TODO(geraki):разобраться с задержками запуска функций, трабла с нулевым значением, временные интервалы не точны
    if (TaskArray[0].delay!=0) {delay_time=TaskArray[0].delay;} // если здесь +1 , то немного работает ))))
    else {delay_time=1;} //можно флаг запуска добавить сюда , но в очереди будет нечего убавлять и ф-ию зациклит
    dt=delay_time;      //или воткнуть туда значение уменьшения , только его нужно брать для точности
    (*tmp.pfunc)();
    flags.RunFlag=0;       //из расчета кол-ва тиков выполняемой функции и частоты прерывания таймера
    // уменьшаем время запуска в списке задач и присваиваем новое время срабатывания счетчику прерывания
    //+ пихать в очередь задачу с нулевой задержкой после следующей в очереди , а не перед , инкреметировать задержку
    //+ чтобы избежать зацикливания , лучше это обработать в очереди
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
// здесь будем кидать на осциллограф
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
   TCCR2 |= (1<<CS02)|(0<<CS01)|(1<<CS00);   // устанавливаем прескалер - 1024(101) 256(100) 64(011) 8(010) 0(001) off(000)
   TIFR = 1<<TOV0;   // очищаем флаг прерывания таймера Т0
   TIMSK |= 1<<TOIE2;   // разрешаем прерывание по переполнению
   TCNT2 = StartFrom;    // загружаем начальное зн. в счетный регистр
   for (i=0; i<MAXnTASKS; i++) DeleteTask(i);   // очищаем массив задач
}
