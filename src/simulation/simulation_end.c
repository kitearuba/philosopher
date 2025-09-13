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

#include "philo.h"

/**
 * @brief Read the end-flag atomically.
 */
int	is_simulation_ended(t_table *table)
{
	int	status;

	pthread_mutex_lock(&table->simulation_lock);
	status = table->simulation_ended;
	pthread_mutex_unlock(&table->simulation_lock);
	return (status);
}

/**
 * @brief End by death: flip end-flag and print the death line atomically.
 */
int	end_simulation_by_death(t_table *t, t_philosophers *who)
{
	int		did_end;
	long	ts;

	did_end = 0;
	pthread_mutex_lock(&t->print_lock);
	pthread_mutex_lock(&t->simulation_lock);
	if (!t->simulation_ended)
	{
		t->simulation_ended = 1;
		did_end = 1;
	}
	pthread_mutex_unlock(&t->simulation_lock);
	if (did_end)
	{
		ts = get_time_in_ms() - t->start_time;
		printf("%ld %d dies\n", ts, who->id);
	}
	pthread_mutex_unlock(&t->print_lock);
	return (did_end);
}

/**
 * @brief End when everyone reached max_meals: flip flag under print_lock fence.
 */
int	end_simulation_all_fed(t_table *t)
{
    int	did_end;

    pthread_mutex_lock(&t->print_lock);
    pthread_mutex_lock(&t->simulation_lock);
    did_end = !t->simulation_ended;
    if (did_end)
        t->simulation_ended = 1;
    pthread_mutex_unlock(&t->simulation_lock);
    pthread_mutex_unlock(&t->print_lock);
    return (did_end);
}