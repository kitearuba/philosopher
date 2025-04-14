/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/07 23:03:30 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/philo.h"

/**
 * @brief Parses and validates command-line arguments.
 *
 * Converts the provided arguments into numeric values stored in the table.
 * Checks for argument count, range, and validity. Enables or disables
 * colored logging based on philosopher count.
 *
 * @param table Pointer to the simulation's table structure.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on success, 1 if an error occurred.
 */
static int	parse_args(t_table *table, int argc, char **argv)
{
	int	error;

	if (argc < 5 || argc > 6)
		return (printf("Error: wrong number of args\n"), 1);
	table->num_philo = safe_atoi(argv[1], &error);
	table->time_to_die = safe_atoi(argv[2], &error);
	table->time_to_eat = safe_atoi(argv[3], &error);
	table->time_to_sleep = safe_atoi(argv[4], &error);
	table->log_colored = 1;
	if (table->num_philo > 50)
		table->log_colored = 0;
	if (argc == 6)
		table->max_meals = safe_atoi(argv[5], &error);
	else
		table->max_meals = -1;
	if (error || table->num_philo < 1 || table->time_to_die < 1
		|| table->time_to_eat < 1 || table->time_to_sleep < 1
		|| (argc == 6 && table->max_meals < 1))
	{
		printf("Error: wrong input\n");
		return (1);
	}
	return (0);
}

/**
 * @brief Allocates memory for philosophers and forks.
 *
 * Allocates and assigns memory for the philosopher array and fork mutexes.
 * On allocation failure, prints an error and frees previously allocated memory.
 *
 * @param table Pointer to the simulation table structure.
 * @return 0 on success, 1 on allocation failure.
 */
static int	allocate_simulation_memory(t_table *table)
{
	table->philosophers = malloc(sizeof(t_philosophers) * table->num_philo);
	if (!table->philosophers)
		return (printf("Error: malloc failed\n"), 1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (!table->forks)
	{
		free(table->philosophers);
		return (printf("Error: malloc failed\n"), 1);
	}
	return (0);
}

/**
 * @brief Initializes global mutexes used in the simulation.
 *
 * Initializes all necessary mutexes for print locking, death detection,
 * tracking philosophers who have eaten, and simulation end control.
 *
 * @param table Pointer to the simulation table.
 * @return 0 on success, 1 on failure.
 */
static int	init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->print_lock, NULL)
		|| pthread_mutex_init(&table->death_lock, NULL)
		|| pthread_mutex_init(&table->fed_lock, NULL)
		|| pthread_mutex_init(&table->simulation_lock, NULL))
	{
		printf("Error: mutex init failed\n");
		return (1);
	}
	return (0);
}

/**
 * @brief Initializes philosopher structures and fork mutexes.
 *
 * Sets default values for each philosopher and initializes fork mutexes.
 * Also links each philosopher to the shared table structure.
 *
 * @param table Pointer to the simulation table.
 */
static void	init_philosopher_data(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
		pthread_mutex_init(&table->forks[i++], NULL);
	i = 0;
	while (i < table->num_philo)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].meals_eaten = 0;
		table->philosophers[i].last_meal_time = 0;
		table->philosophers[i].table = table;
		i++;
	}
}

/**
 * @brief Initializes the simulation by parsing input, allocating memory,
 *        initializing mutexes, and preparing philosopher data.
 *
 * This function is called once in main before starting the threads.
 *
 * @param table Pointer to the table structure (already allocated in main).
 * @param argc Argument count.
 * @param argv Argument values.
 * @return 0 on success, 1 on failure.
 */
int	init_simulation(t_table *table, int argc, char **argv)
{
	if (parse_args(table, argc, argv))
	{
		free(table);
		return (1);
	}
	if (allocate_simulation_memory(table))
		return (1);
	if (init_mutexes(table))
		return (1);
	table->someone_died = 0;
	table->total_fed = 0;
	table->simulation_ended = 0;
	init_philosopher_data(table);
	return (0);
}
