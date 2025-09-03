/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:02:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/21 22:03:59 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int is_simulation_ended(t_table *table)
{
    int status;

    pthread_mutex_lock(&table->simulation_lock);
    status = table->simulation_ended;
    pthread_mutex_unlock(&table->simulation_lock);
    return (status);
}

/* Death ends the sim and prints exactly one line. */
int end_simulation_by_death(t_table *t, t_philosophers *who)
{
    int did_end = 0;

    /* Serialize with printers first. */
    pthread_mutex_lock(&t->print_lock);

    pthread_mutex_lock(&t->simulation_lock);
    if (!t->simulation_ended) {
        t->simulation_ended = 1;
        did_end = 1;
    }
    pthread_mutex_unlock(&t->simulation_lock);

    if (did_end) {
        /* Print death while we still hold print_lock so nothing interleaves. */
        long ts = get_time_in_ms() - t->start_time;
        printf("%ld %d dies\n", ts, who->id);
    }
    pthread_mutex_unlock(&t->print_lock);
    return did_end;
}

/* All-fed ends the sim but prints nothing. We still fence with print_lock. */
int end_simulation_all_fed(t_table *t)
{
    int did_end = 0;

    pthread_mutex_lock(&t->print_lock);

    pthread_mutex_lock(&t->simulation_lock);
    if (!t->simulation_ended) {
        t->simulation_ended = 1;
        did_end = 1;
    }
    pthread_mutex_unlock(&t->simulation_lock);

    pthread_mutex_unlock(&t->print_lock);
    return did_end;
}
