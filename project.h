#ifndef _PROJECT_H
#define _PROJECT_H
/***********DEFINES************/
//---------bmp280.c-----------
#define I2CADDR 0x76
//---------max7219.c-----------
#define DATA        27 // (WiringPi pin num 27)
#define LOAD        28 // (WiringPi pin num 28)
#define CLOCK       29 // (WiringPi pin num 29)
// The Max7219 Registers :
#define DECODE_MODE   0x09
#define INTENSITY     0x0a
#define SCAN_LIMIT    0x0b
#define SHUTDOWN      0x0c
#define DISPLAY_TEST  0x0f

/***********FUNCTIONS************/
//---------max7219.c-----------
void Send16bits (unsigned short output);
void MAX7219Send (unsigned char reg_number, unsigned char dataout);
void SetupConfig();
void display_luminosity();
void display_pressure();
//---------bh1750.c-----------
int measureLuminosity();
//---------bmp280.c-----------
int measurePressure();
//---------thread.c-----------
void *bh1750(void *arg);
void *bmp280(void *arg);
void *max7219();
//---------signal.c-----------
void sig_handler(int sig);

/***********VARIABLES************/
//---------main.c-----------
#include <semaphore.h>
#include <pthread.h>
sem_t sem1, sem2, sem_start;
pthread_t t1, t2, t3;
int *lux;               //return value bh1750
double *hPa;            //return value bmp280

#endif