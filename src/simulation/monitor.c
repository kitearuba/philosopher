/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/05/10 21:52:20 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Checks if a philosopher has died from not eating in time.
 *
 * Compares the current time to the philosopher's last meal time.
 * If the time exceeds time_to_die, logs the death message, sets
 * the simulation end flag, and returns 1.
 *
 * @param table Pointer to the simulation table.
 * @param i Index of the philosopher to check.
 * @return 1 if the philosopher has died, 0 otherwise.
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
 * @brief Checks if all philosophers have eaten the required number of meals.
 *
 * If max_meals is defined, and total_fed is equal to or exceeds num_philo,
 * logs the completion message and ends the simulation.
 *
 * @param table Pointer to the simulation table.
 * @return 1 if all philosophers are fed, 0 otherwise.
 */
static int	check_all_ate(t_table *table)
{
	int	all_fed;

	if (table->max_meals <= 0)
		return (0);
	pthread_mutex_lock(&table->fed_lock);
	all_fed = (table->total_fed >= table->num_philo);
	pthread_mutex_unlock(&table->fed_lock);
	if (!all_fed)
		return (0);
	end_simulation_all_fed(table);
	return (1);
}

/**
 * @brief Monitoring thread that detects death or completion conditions.
 *
 * Loops continuously while the simulation is active.
 * Checks each philosopher for starvation and verifies if all
 * have reached the max_meals threshold. Ends the simulation
 * immediately if any of these conditions are met.
 *
 * @param arg Pointer to the shared simulation table.
 * @return NULL when monitoring ends.
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
