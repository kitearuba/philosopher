/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:21:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/05/10 21:50:36 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Initializes each philosopher and starts their threads.
 *
 * This function sets the simulation's start time, initializes each
 * philosopher's ID, last meal timestamp, and links to the shared table data.
 * Then, it creates a thread for each philosopher to run their routine
 * concurrently.
 *
 * @param table Pointer to the simulation's table structure.
 */

static void	start_simulation(t_table *table)
{
	int			i;

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

static int	exit_simulation(t_table *table, int code)
{
	cleanup_simulation(table);
	free(table);
	return (code);
}

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

	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	memset(table, 0, sizeof(t_table));
	i = 0;
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
