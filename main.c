/*
 * Copyright (c) 2022 Hugues Larrive <hlarrive@pm.me>
 *
 * SPDX-License-Identifier: CECILL-2.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"
#include "../modules/hrtim/hrtim.h"
#include "xtimer.h"

static int cmd_fan(int argc, char**argv)
{
    if (argc != 2) {
        printf("usage: %s <power>\n", argv[0]);
        puts("\tpower: fan power in %");
        return 1;
    }

    uint8_t power = atoi(argv[1]);
    if (power < 1 || power > 100) {
        printf("Error: invalid power: %d\n", power);
        return 1;
    }

    hrtim_pwm_set(0, TIMB, (11200 * power / 100), 0);
    return 0;
}

static const shell_command_t shell_commands[] = {
    { "fan", "Set fan power in percent", cmd_fan },
    { NULL, NULL, NULL }
};

int main(void)
{
    puts("HRTIM peripheral driver test\n");

    uint32_t freq;

    /** - Initialize the master timer, TIMA and TIMB at 250KHz frequency */
    freq = KHZ(250);
    hrtim_init_master(0, &freq);
    hrtim_init_tu(0, TIMA, &freq);
    hrtim_init_tu(0, TIMB, &freq);

    /** - Set 200ns dead-time for TIMB */
    hrtim_pwm_dt(0, TIMB, 200);

    /** - Enable counters */
    hrtim_cnt_en(0, (MCEN | TACEN | TBCEN));

    /** - Set TIMA output 1 high and output 2 low for boost operation */
    hrtim_cmpl_pwm_out(0, TIMA);
    hrtim_set_cb_set(0, TIMA, OUT1, PER);   /* PA8  P1 Drive */
    //~ hrtim_set_cb_set(0, TIMA, OUT2, PER);   /* PA9  N1 Drive */
    hrtim_out_en(0, TIMA, OUT1);

    /** - Set complementary outputs and 60% duty-cycle for TIMB */
    /* TIMB OUT1    PA10     N2 Drive */
    /* TIMB OUT2    PA11     P2 Drive */
    hrtim_cmpl_pwm_out(0, TIMB);
    hrtim_pwm_set(0, TIMB, 1120, 0);
    hrtim_out_en(0, TIMB, (OUT1 | OUT2));

    /** - Need a soft start */
    for (uint16_t p = 1120; p <= 11200; p += 1120) {
        xtimer_sleep(1);
        printf("p = %d\n", p);
        hrtim_pwm_set(0, TIMB, p, 0);
    }
    
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
