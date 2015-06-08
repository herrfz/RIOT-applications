#include <string.h>
#include <stdlib.h>

#include "periph/gpio.h"
#include "vtimer.h"

#include "03oos_openwsn.h"


int main(void) 
{
    int unpressed, state = 0;
    int argc = 2;
    char **argv;

    argv = malloc(argc * sizeof(char*));
    for (int i = 0; i < argc; i++) {
        argv[i] = malloc(sizeof(char));
    }

    timex_t begin, end;
    timex_t period = timex_set(0, 0);
    gpio_init_in(GPIO_0, GPIO_NOPULL);

    while(1) { // measure how long the buttton is pressed
        unpressed = gpio_read(GPIO_0);
        if (!unpressed && state == 0) {
            state = 1;
            vtimer_now(&begin);
        } else if (unpressed && state == 1) {
            state = 0;
            vtimer_now(&end);
            period = timex_sub(end, begin);
            break;
        }
    }

    if (period.seconds < 1) {
        strcpy(argv[1], "n"); // short press: start as node
    } else {
        strcpy(argv[1], "r"); // long press: start as root
    }

    openwsn_start_thread(argc, argv); // start openwsn

    return 0;
}
