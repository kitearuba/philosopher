/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/09/13 22:26:37 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Destroy all mutexes and free dynamic memory.
 */
void	cleanup_simulation(t_table *table)
{
	int	i;

	if (!table)
		return ;
	if (table->philosophers)
	{
		i = 0;
		while (i < table->num_philo)
			pthread_mutex_destroy(&table->philosophers[i++].state_lock);
	}
	if (table->forks)
	{
		i = 0;
		while (i < table->num_philo)
			pthread_mutex_destroy(&table->forks[i++]);
		free(table->forks);
		table->forks = NULL;
	}
	if (table->philosophers)
	{
		free(table->philosophers);
		table->philosophers = NULL;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->fed_lock);
	pthread_mutex_destroy(&table->simulation_lock);
}

/**
 * @brief Free the table and return exit code.
 */
int	exit_simulation(t_table *table, int code)
{
	cleanup_simulation(table);
	free(table);
	return (code);
}
