/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:21:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/06/24 10:23:02 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Entry point of the philosophers simulation.
 *
 * Allocates memory for the simulation table, initializes the simulation
 * parameters and resources, handles the special case where max_meals is zero
 * (instant finish), starts the philosopher threads and the monitor thread,
 * waits for all threads to complete, and finally cleans up before exiting.
 *
 * @param argc Argument count.
 * @param argv Argument values.
 * @return int Exit status.
 */
int	main(int argc, char **argv)
{
	t_table		*table;
	pthread_t	monitor;
	int			i;

	i = 0;
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	memset(table, 0, sizeof(t_table));
	if (init_simulation(table, argc, argv))
		return (exit_simulation(table, 1));
	if (table->max_meals == 0)
		return (exit_simulation(table, 0));
	start_simulation(table);
	pthread_create(&monitor, NULL, monitor_death, table);
	pthread_join(monitor, NULL);
	while (i < table->num_philo)
		pthread_join(table->philosophers[i++].thread, NULL);
	return (exit_simulation(table, 0));
}
