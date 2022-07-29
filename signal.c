#include <stdlib.h>
#include <signal.h>
#include "project.h"

void sig_handler(int sig)
{
    exit(0);                // Signal, das die Funktion in der es aufgerufen wird beendet
}