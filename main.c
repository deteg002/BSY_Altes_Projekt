//**********
//
// BSY Projektarbeit
// Gruppe 49; Aufgabe 31; Pi 16
// Luca Hilger, Dennis Tegelaers
//
//**********

#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdlib.h>
#include "project.h"

    int main(void) {

        signal(SIGALRM, sig_handler); // signal wird erzeugt und ruft funktion "sig_handler" auf, sobald einige Zeit vorüber geht
        alarm(60); // Der Alarm des Signals wird auf 60 Sekunden gestellt 
        

        sem_init(&sem1, 0, 0);   // erster parameter address der semaphore, zweiter 0 wenn ohne prozess gearbeitet wird, dritter Counter
        sem_init(&sem2, 0, 0);
        sem_init(&sem_start, 0, 1);

        SetupConfig();

        if (pthread_create(&t1, NULL, &bh1750, &lux) != 0) {    // thread 1 mit Funktion bh1750 erstellt, lux als Argument
            return 1;
        }
        if (pthread_create(&t2, NULL, &bmp280, &hPa) != 0) {    // thread 2 mit Funktion bmp280 erstellt, hPa als Argument
            return 1;
        }
        if (pthread_create(&t3, NULL, &max7219, NULL) != 0) {   // thread 3 mit Funktion max7219 erstellt, ohne Argument
            return 1;
        }

        pthread_join(t3, NULL); // Main wird beendet wenn Thread 3 beendet wurde

        sem_destroy(&sem1); // zerstört Semaphore auf die gezeigt wird
        sem_destroy(&sem2);
        sem_destroy(&sem_start);

        return 0;
    }