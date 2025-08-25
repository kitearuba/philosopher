/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/05/10 22:01:45 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Cleans up simulation resources.
 *
 * Destroys all fork and shared mutexes, and frees memory
 * for philosophers and forks.
 *
 * @param table Pointer to the simulation table.
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
 * @brief Handles memory cleanup and exits the program.
 *
 * Frees all allocated resources, including mutexes and philosophers.
 * Frees the main table structure itself.
 * Returns the given exit code to the operating system.
 *
 * @param table Pointer to the simulation table.
 * @param code Exit code to return.
 * @return int Exit code.
 */

int	exit_simulation(t_table *table, int code)
{
	cleanup_simulation(table);
	free(table);
	return (code);
}