/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup tests
 * @{
 *
 * @file
 * @brief       Test application for OpenWSN pkg
 *
 * @author      Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>

#include "vtimer.h"
#include "shell.h"
#include "posix_io.h"
#include "board_uart0.h"
#include "riot.h"

#include "board.h"

#include "03oos_openwsn.h"

#define MSEC 1000
#define SEC  (1000 * MSEC)

static char stack_buffer[KERNEL_CONF_STACKSIZE_MAIN];

const shell_command_t shell_commands[] = {
    {"owsn_init", "Start OpenWSN", openwsn_start_thread},
    {NULL, NULL, NULL}
};

void* blink(void *arg)
{
    (void)arg;
    LED_GREEN_ON;
    vtimer_usleep(SEC);
    while(1)
    {
        LED_GREEN_TOGGLE;
        vtimer_usleep(SEC);
    }

}

static int shell_readc(void)
{
    char c = 0;
    (void) posix_read(uart0_handler_pid, &c, 1);
    return c;
}

static void shell_putchar(int c)
{
    (void) putchar(c);
}

int main(void) {
    shell_t shell;
    
    (void) posix_open(uart0_handler_pid, 0);

    puts("Welcome to RIOT!");

    thread_create(stack_buffer, sizeof(stack_buffer),
                  PRIORITY_MAIN - 2, CREATE_STACKTEST,
                  blink, NULL, "blink");

    shell_init(&shell, shell_commands, UART0_BUFSIZE, shell_readc, shell_putchar);

    shell_run(&shell);

    return 0;
}