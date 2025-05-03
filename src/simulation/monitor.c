/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/21 22:01:21 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Checks if a philosopher has died from not eating in time.
 *
 * Compares the current time to the philosopher's last meal time.
 * If the time exceeds time_to_die, marks the simulation as ended.
 *
 * @param table Pointer to the simulation table.
 * @param i Index of the philosopher to check.
 * @return 1 if the philosopher has died, 0 otherwise.
 */
static int	check_death(t_table *table, int i)
{
	long	time;

	time = get_time_in_ms() - table->philosophers[i].last_meal_time;
	if (time > table->time_to_die)
	{
		set_simulation_end(table);
		return (1);
	}
	return (0);
}

/**
 * @brief Checks if all philosophers have eaten the required number of meals.
 *
 * If max_meals is set, and the total number of fully fed philosophers
 * is equal to or greater than num_philo, the simulation ends.
 *
 * @param table Pointer to the simulation table.
 * @return 1 if all philosophers are fed, 0 otherwise.
 */
static int	check_all_ate(t_table *table)
{
	if (table->max_meals > 0)
	{
		if (table->total_fed >= table->num_philo)
		{
			set_simulation_end(table);
			return (1);
		}
	}
	return (0);
}

/**
 * @brief Monitoring thread that detects death or completion conditions.
 *
 * Continuously checks if any philosopher has died or if all philosophers
 * have eaten enough. Ends the simulation when one of these conditions is met.
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
		    {
		        pthread_mutex_lock(&table->death_print_lock);
		        print_action(&table->philosophers[i], "died");
		        pthread_mutex_unlock(&table->death_print_lock);
		        return (NULL);
		    }
			i++;
		}
		if (check_all_ate(table))
			return (NULL);
		ft_usleep(1, table);
	}
	return (NULL);
}
