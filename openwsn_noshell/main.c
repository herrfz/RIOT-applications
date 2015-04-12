#include <stdio.h>

#include "shell.h"
#include "shell_commands.h"
#include "posix_io.h"
#include "01bsp_radiotimer.h"
#include "board_uart0.h"
#include "riot.h"

#include "thread.h"
#include "board.h"
#include "vtimer.h"

static char stack_buffer[KERNEL_CONF_STACKSIZE_MAIN];

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

int main(void) 
{
    shell_t shell;
    (void) posix_open(uart0_handler_pid, 0);

    puts("Welcome to RIOT!");

    thread_create(stack_buffer,  sizeof(stack_buffer),
                  PRIORITY_MAIN - 2, CREATE_STACKTEST,
                  mote_main, NULL, "mote_main");

    shell_init(&shell, NULL, UART0_BUFSIZE, shell_readc, shell_putchar);
    shell_run(&shell);

    return 0;
}
