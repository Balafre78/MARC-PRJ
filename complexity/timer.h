//
// Created by Raphy on 21/11/2024.
//

#ifndef MARC_PRJ_TIMER_H
#define MARC_PRJ_TIMER_H

#include <time.h>

typedef struct s_timer
{
    clock_t start;
    clock_t end;
} t_timer;

/**
 * @brief Create a timer
 * @return timer
 */
t_timer createTimer();

/**
 * @brief Start a timer
 * @param timer to start
 */
void startTimer(t_timer *timer);

/**
 * @brief Stop a timer
 * @param timer to stop
 */
void stopTimer(t_timer *timer);

/**
 * @brief Display a timer
 * @param timer to display
 */
void displayTimer(t_timer *timer);

#endif //MARC_PRJ_TIMER_H
