/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/09/14 23:21:28 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_philo_mutexes(t_table *t)
{
	int	i;

	if (!t->philosophers)
		return ;
	i = 0;
	while (i < t->num_philo)
	{
		pthread_mutex_destroy(&t->philosophers[i].state_lock);
		i++;
	}
}

static void	destroy_forks_and_free(t_table *t)
{
	int	i;

	if (!t->forks)
		return ;
	i = 0;
	while (i < t->num_philo)
	{
		pthread_mutex_destroy(&t->forks[i]);
		i++;
	}
	free(t->forks);
	t->forks = NULL;
}

static void	destroy_global_mutexes(t_table *t)
{
	pthread_mutex_destroy(&t->print_lock);
	pthread_mutex_destroy(&t->fed_lock);
	pthread_mutex_destroy(&t->simulation_lock);
}

/**
 * @brief Destroy all mutexes and free dynamic memory.
 */
void	cleanup_simulation(t_table *table)
{
	if (!table)
		return ;
	destroy_philo_mutexes(table);
	destroy_forks_and_free(table);
	if (table->philosophers)
	{
		free(table->philosophers);
		table->philosophers = NULL;
	}
	destroy_global_mutexes(table);
}

/**
 * @brief Free the table and return exit code.
 */
int	exit_simulation(t_table *table, int code)
{
	cleanup_simulation(table);
	free(table);
	return (code);
}
