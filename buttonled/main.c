/*
 * Copyright (C) 2014 Eriza Fazli 
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
 * @brief       Test user button and LED
 *
 * @author      Eriza Fazli <erizzaaaaa@gmail.com>
 *
 * @}
 */

#include <stdio.h>

#include "board.h"
#include "periph/gpio.h"
#include "vtimer.h"

#define ACTIVE_FLANK        GPIO_RISING
#define PULL                GPIO_NOPULL

timex_t now;

void g0_cb(void *arg){
    vtimer_now(&now);
    printf("now is %lu.%lu seconds\n", now.seconds, now.microseconds);
    LED_GREEN_TOGGLE;
}

int main(void)
{
    gpio_init_int(GPIO_0, PULL, ACTIVE_FLANK, g0_cb, 0);
    return 0;
}
