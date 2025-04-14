/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/07 23:07:49 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Initializes and starts the simulation by creating a thread for each philosopher.
 *
 * This function sets the simulation's start time and initializes each philosopher's
 * ID, last meal time, and pointer to the shared table. It then creates a thread
 * for each philosopher to run their routine concurrently.
 *
 * @param table Pointer to the simulation's table structure.
 */
static void	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time_in_ms();
	while (i < table->num_philo)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].last_meal_time = table->start_time;
		table->philosophers[i].table = table;
		pthread_create(&table->philosophers[i].thread,
			NULL,
			philo_routine,
			&table->philosophers[i]);
		i++;
	}
}

/**
 * @brief Entry point of the simulation program.
 *
 * This function allocates the table structure, initializes the simulation,
 * starts the philosopher threads, and launches the monitor thread. It then
 * waits for all threads to finish, optionally prints the meal summary,
 * and performs cleanup.
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

	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	i = 0;
	if (init_simulation(table, argc, argv))
		return (1);
	start_simulation(table);
	pthread_create(&monitor, NULL, monitor_death, table);
	pthread_join(monitor, NULL);
	while (i < table->num_philo)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
	if (table->num_philo < 20)
		print_meal_summary(table);
	cleanup_simulation(table);
	free(table);
	return (0);
}