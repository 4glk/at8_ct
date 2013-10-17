#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "macros.h"

/// Типы данных //
typedef unsigned char u8;
typedef unsigned int u16;
typedef struct task{
   void (*pfunc) (void);    // указатель на функцию
   u16 delay;               // задержка перед первым запуском задачи
   u16 period;              // период запуска задачи
   u8 run;                  // флаг готовности задачи к запуску
}task;                      // флаг запуска можно вынести за структуру

//typedef enum boolean{FALSE,TRUE}boolean;
//bool runFlag=FALSE;
//uint16_t *delay_time_ptr;
uint16_t delay_time;
        uint16_t dt;
extern uint16_t timer2;

/// Определения ///////////
// Константа для таймера Т0
// 25 мс при тактовой частоте
// 8 МГц и предделителе 1024
//#define StartFrom       0x3D //для 25 мс 40Гц
#define StartFrom       0xF8 //для 1 мс 1КГц            //на большой частоте висит в убр регистре
//#define StartFrom       0xB2 //для 10 мс 100Гц        //недостаточно для индикации
// максимальное количество задач
#define MAXnTASKS       8
//Константа для UART`a
//скорость обмена 9600 при частоте 8 МГц
#define UBRRvalue 0x0033
//#define UART
//#define OSC

/// Массив задач ///////////
volatile task TaskArray[MAXnTASKS];

/// Прототипы фукнций ////////
#ifdef UART
void InitUART (u16 baud);       //инициализация юарта
void TransmitByte (u8 data);    //передача байта по юарту
#endif
void InitScheduler (void);      //инициализация диспетчера
void UpdateScheduler(void);     //обновление диспетчера
void DeleteTask (u8 index);     //удаление задачи
//TODO:нужно научить эту функцию брать указатель на функцию с любыми аргументами и без них
void AddTask (void (*taskfunc)(void), u16 taskdelay, u16 taskperiod);   //добавление задачи
void DispatchTask (void);       //собсна сам диспетчер и запуск задачи по флагу
#ifdef UART
void TestA (void);
void TestB (void);
//void TestC (void);
//void TestD (void);
//void TestE (void);
//void TestF (void);
//void TestG (void);
//void TestH (void);
//void TestI (void);
#endif // UART
#ifdef OSC
void Debug_osc_a(void);
//void Debug_osc_b(void);
//void Debug_osc_c(void);
//void Debug_osc_d(void);
#endif
