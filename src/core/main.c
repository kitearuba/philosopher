/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:21:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/09/13 19:11:19 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Program entry point: init, start threads, run monitor, join, exit.
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
	if (pthread_create(&monitor, NULL, monitor_death, table) != 0)
		return (exit_simulation(table, 1));
	pthread_join(monitor, NULL);
	while (i < table->num_philo)
		pthread_join(table->philosophers[i++].thread, NULL);
	return (exit_simulation(table, 0));
}
