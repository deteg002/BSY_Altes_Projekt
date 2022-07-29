#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "project.h"

void *bh1750(void *arg){
    while(1) {
        sem_wait(&sem_start);
        *((int*)arg) = measureLuminosity();         //void pointer wird zu int gecasted und dereferenziert
        printf("bh1750 Lux: %d\n", *((int*)arg));
        sem_post(&sem1);
    }
};

void *bmp280(void *arg){
    while(1) {
        sem_wait(&sem1);
        *((int*)arg) = measurePressure();           //void pointer wird zu int gecasted und dereferenziert
        printf("bmp280 Bar: %d\n", *((int*)arg));
        sem_post(&sem2);
    }
};

void *max7219(){
    int i = 0;
    while(1) {
        sem_wait(&sem2);
        MAX7219Send(SHUTDOWN, 1);      // come out of shutdown mode // turn on the digits
        display_luminosity(measureLuminosity());
        display_pressure(measurePressure());
        sleep(15);
        sem_post(&sem_start);
    }
};