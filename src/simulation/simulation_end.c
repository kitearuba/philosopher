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
 * @brief Checks if the simulation has ended.
 *
 * Uses a mutex to safely read the `simulation_ended` flag.
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
 * @brief Sets the simulation end flag to true.
 *
 * Uses a mutex to safely update the `simulation_ended` value.
 *
 * @param table Pointer to the simulation table.
 */
void	set_simulation_end(t_table *table)
{
	pthread_mutex_lock(&table->simulation_lock);
	table->simulation_ended = 1;
	pthread_mutex_unlock(&table->simulation_lock);
}
