/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/09/14 22:11:00 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief If (now - last_meal) >= time_to_die → end by death.
 */
static int	check_death(t_table *table, int i)
{
	long	now;
	long	last;
	long	elapsed;

	now = get_time_in_ms();
	pthread_mutex_lock(&table->philosophers[i].state_lock);
	last = table->philosophers[i].last_meal_time;
	pthread_mutex_unlock(&table->philosophers[i].state_lock);
	elapsed = now - last;
	if (elapsed >= table->time_to_die)
	{
		end_simulation_by_death(table, &table->philosophers[i]);
		return (1);
	}
	return (0);
}

/**
 * @brief If max_meals active and all fed → end (no print).
 */
static int	check_all_ate(t_table *table)
{
	int	all_fed;

	if (table->max_meals <= 0)
		return (0);
	pthread_mutex_lock(&table->fed_lock);
	all_fed = (table->total_fed >= table->num_philo);
	pthread_mutex_unlock(&table->fed_lock);
	if (all_fed)
	{
		end_simulation_all_fed(table);
		return (1);
	}
	return (0);
}

/**
 * @brief Monitor loop: stop on death or all-fed.
 */
void	*monitor_death(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!is_simulation_ended(table))
	{
		i = 0;
		while (i < table->num_philo)
		{
			if (check_death(table, i))
				return (NULL);
			i++;
		}
		if (check_all_ate(table))
			return (NULL);
		ft_usleep(1, table);
	}
	return (NULL);
}
