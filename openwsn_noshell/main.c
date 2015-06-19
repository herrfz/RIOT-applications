#include <string.h>
#include <stdlib.h>

#include "periph/gpio.h"
#include "vtimer.h"

#include "03oos_openwsn.h"


int main(void) 
{
    int argc = 2;
    char **argv;

    argv = malloc(argc * sizeof(char*));
    for (int i = 0; i < argc; i++) {
        argv[i] = malloc(sizeof(char));
    }

    strcpy(argv[1], "n");

    openwsn_start_thread(argc, argv); // start openwsn

    return 0;
}
