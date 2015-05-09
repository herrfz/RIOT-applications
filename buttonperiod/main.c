/*
 * Copyright (C) 2015 Eriza Fazli 
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup applications 
 * @{
 *
 * @file
 * @brief       measure how long a button is pressed
 *
 * @author      Eriza Fazli <erizzaaaaa@gmail.com>
 *
 * @}
 */

#include <stdio.h>

#include "periph/gpio.h"
#include "vtimer.h"

int main(void)
{
    int unpressed, state = 0;
    timex_t begin, end;
    timex_t period = timex_set(0, 0);
    gpio_init_in(GPIO_0, GPIO_NOPULL);

    while (1) {
        unpressed = gpio_read(GPIO_0);
        if (!unpressed && state == 0) {
            state = 1;
            vtimer_now(&begin);
        } else if (unpressed && state == 1) {
            state = 0;
            vtimer_now(&end);
            period = timex_sub(end, begin);
            printf("button is pressed for %lu.%lu seconds\n", period.seconds, period.microseconds);
        }
    }

    return 0;
}
