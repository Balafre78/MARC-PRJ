//
// Created by Raphy on 21/11/2024.
//

#include <stdio.h>
#include "timer.h"

t_timer createTimer()
{
    t_timer timer;
    timer.start = 0;
    timer.end = 0;
    return timer;
}

void startTimer(t_timer *timer)
{
    timer->start = clock();
}

void stopTimer(t_timer *timer)
{
    timer->end = clock();
}

void displayTimer(t_timer *timer)
{
    double time = (1000.0 * (double) (timer->end - timer->start)) / CLOCKS_PER_SEC;
    int msecs = (int) (time) % 1000;
    int secs = (int) (time) / 1000;
    printf("%ds %dms\n", secs, msecs);
}