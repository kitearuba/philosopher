/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:21:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/09/13 22:24:00 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief start_simulation: stamp start time and spawn philosopher threads.
 */
void	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time_in_ms();
	while (i < table->num_philo)
	{
		table->philosophers[i].last_meal_time = table->start_time;
		if (pthread_create(&table->philosophers[i].thread,
				NULL, philo_routine, &table->philosophers[i]) != 0)
		{
			end_simulation_all_fed(table);
			break ;
		}
		i++;
	}
}
