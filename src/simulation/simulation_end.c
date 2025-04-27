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

/**
 * @brief Checks if the simulation has ended in a thread-safe way.
 *
 * Locks the simulation mutex, reads the simulation_ended flag, then unlocks.
 *
 * @param table Pointer to the simulation table.
 * @return 1 if simulation has ended, 0 otherwise.
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
 * @brief Marks the simulation as ended in a thread-safe way.
 *
 * Locks the simulation mutex, sets simulation_ended to 1, then unlocks.
 *
 * @param table Pointer to the simulation table.
 */
void	set_simulation_end(t_table *table)
{
	pthread_mutex_lock(&table->simulation_lock);
	table->simulation_ended = 1;
	pthread_mutex_unlock(&table->simulation_lock);
}
