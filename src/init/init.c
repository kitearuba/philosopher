/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/06/24 22:55:00 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Parse and validate CLI args into the table.
 *        All values must be strictly positive; optional max_meals can be absent.
 */
static t_status	parse_args(t_table *table, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Error: wrong number of args\n"), FAILURE);
	table->num_philo = safe_atoi(argv[1]);
	table->time_to_die = safe_atoi(argv[2]);
	table->time_to_eat = safe_atoi(argv[3]);
	table->time_to_sleep = safe_atoi(argv[4]);
	if (argc == 6)
		table->max_meals = safe_atoi(argv[5]);
	else
		table->max_meals = -1;
	if (table->num_philo < 1 || table->time_to_die < 1
		|| table->time_to_eat < 1 || table->time_to_sleep < 1
		|| (argc == 6 && table->max_meals < 1))
		return (printf("Error: wrong input\n"), FAILURE);
	return (SUCCESS);
}

/**
 * @brief Allocate arrays for philosophers and fork mutexes.
 */
static t_status	allocate_simulation_memory(t_table *table)
{
	table->philosophers = malloc(sizeof(t_philosophers) * table->num_philo);
	if (!table->philosophers)
		return (printf("Error: malloc failed\n"), FAILURE);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (!table->forks)
	{
		free(table->philosophers);
		table->philosophers = NULL;
		return (printf("Error: malloc failed\n"), FAILURE);
	}
	return (SUCCESS);
}

/**
 * @brief Create global mutexes used across the simulation.
 */
static t_status	init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->print_lock, NULL)
		|| pthread_mutex_init(&table->fed_lock, NULL)
		|| pthread_mutex_init(&table->simulation_lock, NULL))
		return (printf("Error: mutex init failed\n"), FAILURE);
	return (SUCCESS);
}

/**
 * @brief Initialize per-philosopher fields and one mutex per fork.
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
		table->philosophers[i].is_fed = 0;
		table->philosophers[i].last_meal_time = 0;
		pthread_mutex_init(&table->philosophers[i].state_lock, NULL);
		table->philosophers[i].has_left_fork = 0;
		table->philosophers[i].has_right_fork = 0;
		table->philosophers[i].table = table;
		i++;
	}
}

/**
 * @brief Top-level initializer called by main().
 */
t_status	init_simulation(t_table *table, int argc, char **argv)
{
	if (parse_args(table, argc, argv) != SUCCESS)
		return (FAILURE);
	if (allocate_simulation_memory(table) != SUCCESS)
		return (FAILURE);
	if (init_mutexes(table) != SUCCESS)
		return (FAILURE);
	table->total_fed = 0;
	table->simulation_ended = 0;
	init_philosopher_data(table);
	return (SUCCESS);
}