/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 23:09:43 by chrrodri          #+#    #+#             */
/*   Updated: 2025/09/14 23:10:01 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_status	init_forks_array(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->num_philo)
	{
		if (pthread_mutex_init(&t->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&t->forks[i]);
			return (failure);
		}
		i++;
	}
	return (success);
}

t_status	init_philos_array(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->num_philo)
	{
		t->philosophers[i].id = i + 1;
		t->philosophers[i].meals_eaten = 0;
		t->philosophers[i].is_fed = 0;
		t->philosophers[i].last_meal_time = 0;
		t->philosophers[i].has_left_fork = 0;
		t->philosophers[i].has_right_fork = 0;
		t->philosophers[i].table = t;
		if (pthread_mutex_init(&t->philosophers[i].state_lock, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&t->philosophers[i].state_lock);
			return (failure);
		}
		i++;
	}
	return (success);
}
