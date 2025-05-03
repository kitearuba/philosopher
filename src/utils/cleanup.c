/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/24 18:09:17 by chrrodri         ###   ########.fr       */
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
	if (table -> philosophers &&
	    table->num_philo < PHILO_PRINT_CAP)
		print_meal_summary(table);
	if (table->forks)
	{
	    while (i < table->num_philo)
	        pthread_mutex_destroy(&table->forks[i++]);
        free(table->forks);
	}
    if (table->philosophers)
        free(table->philosophers);
    pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->fed_lock);
	pthread_mutex_destroy(&table->death_lock);
	pthread_mutex_destroy(&table->simulation_lock);
    pthread_mutex_destroy(&table->death_print_lock);
}
