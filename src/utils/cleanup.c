/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/21 22:05:19 by chrrodri         ###   ########.fr       */
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

	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->death_print_lock);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->fed_lock);
	pthread_mutex_destroy(&table->death_lock);
	pthread_mutex_destroy(&table->simulation_lock);
	free(table->forks);
	free(table->philosophers);
}
