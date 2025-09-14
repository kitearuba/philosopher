/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/09/14 23:15:34 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Free arrays and optionally destroy forks/global mutexes.
 * destroy_forks: 1 to destroy fork mutexes;
 * destroy_globals: 1 to destroy globals.
 */
static void	cleanup_init_failure(t_table *t, int destroy_forks,
		int destroy_globals)
{
	int	i;

	if (destroy_forks && t->forks)
	{
		i = t->num_philo;
		while (--i >= 0)
			pthread_mutex_destroy(&t->forks[i]);
	}
	if (destroy_globals)
	{
		pthread_mutex_destroy(&t->simulation_lock);
		pthread_mutex_destroy(&t->fed_lock);
		pthread_mutex_destroy(&t->print_lock);
	}
	if (t->forks)
	{
		free(t->forks);
		t->forks = NULL;
	}
	if (t->philosophers)
	{
		free(t->philosophers);
		t->philosophers = NULL;
	}
}

static t_status	parse_args(t_table *t, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of args\n");
		return (failure);
	}
	t->num_philo = safe_atoi(argv[1]);
	t->time_to_die = safe_atoi(argv[2]);
	t->time_to_eat = safe_atoi(argv[3]);
	t->time_to_sleep = safe_atoi(argv[4]);
	if (argc == 6)
		t->max_meals = safe_atoi(argv[5]);
	else
		t->max_meals = -1;
	if (t->num_philo < 1 || t->time_to_die < 1 || t->time_to_eat < 1
		|| t->time_to_sleep < 1 || (argc == 6 && t->max_meals < 1))
	{
		printf("Error: wrong input\n");
		return (failure);
	}
	return (success);
}

static t_status	allocate_simulation_memory(t_table *t)
{
	t->philosophers = malloc(sizeof(t_philo) * t->num_philo);
	if (!t->philosophers)
	{
		printf("Error: malloc failed\n");
		return (failure);
	}
	t->forks = malloc(sizeof(pthread_mutex_t) * t->num_philo);
	if (!t->forks)
	{
		free(t->philosophers);
		t->philosophers = NULL;
		printf("Error: malloc failed\n");
		return (failure);
	}
	return (success);
}

static t_status	init_mutexes(t_table *t)
{
	if (pthread_mutex_init(&t->print_lock, NULL) != 0)
		return (failure);
	if (pthread_mutex_init(&t->fed_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&t->print_lock);
		return (failure);
	}
	if (pthread_mutex_init(&t->simulation_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&t->fed_lock);
		pthread_mutex_destroy(&t->print_lock);
		return (failure);
	}
	return (success);
}

t_status	init_simulation(t_table *t, int argc, char **argv)
{
	if (parse_args(t, argc, argv) != success)
		return (failure);
	if (allocate_simulation_memory(t) != success)
		return (failure);
	if (init_mutexes(t) != success)
	{
		cleanup_init_failure(t, 0, 0);
		return (failure);
	}
	t->total_fed = 0;
	t->simulation_ended = 0;
	if (init_forks_array(t) != success)
	{
		cleanup_init_failure(t, 0, 1);
		return (failure);
	}
	if (init_philos_array(t) != success)
	{
		cleanup_init_failure(t, 1, 1);
		return (failure);
	}
	return (success);
}
