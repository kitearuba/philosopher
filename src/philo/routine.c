/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/07 22:56:05 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	*philosopher_routine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;

	while (1)
	{
		// 🧠 Step 1: Thinking
		print_action(philo, "is thinking");

		// 🍴 Step 2: Taking forks safely (even/odd strategy)
		if (philo->id % 2 == 0)
		{
			// Even ID: Take right fork first
			PM_LOCK(philo->table->forks[philo->id % philo->table->num_philo]);
			print_action(philo, "has taken a fork");

			PM_LOCK(philo->table->forks[philo->id - 1]);
			print_action(philo, "has taken a fork");
		}
		else
		{
			// Odd ID: Take left fork first
			PM_LOCK(philo->table->forks[philo->id - 1]);
			print_action(philo, "has taken a fork");
			PM_LOCK(philo->table->forks[philo->id % philo->table->num_philo]);
			print_action(philo, "has taken a fork");
		}
		// 🍝 Step 3: Eating
		print_action(philo, "is eating");
		philo->last_meal_time = get_time_in_ms();
		ft_usleep(philo->table->time_to_eat);

		// 🔓 Step 4: Releasing forks
		PM_UNLOCK(philo->table->forks[philo->id - 1]);
		PM_UNLOCK(philo->table->forks[philo->id % philo->table->num_philo]);

		// 😴 Step 5: Sleeping
		print_action(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep);
	}

	// This point is never reached in the loop
	return (NULL);
}

/*
void	*philosopher_routine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	while (1)
	{
		print_action(philo, "is thinking");
		pthread_mutex_lock(&philo->table->forks[philo->id -1]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock
			(&philo->table->forks[philo->id % philo->table->num_philosophers]);
		print_action(philo, "has taken a fork");
		print_action(philo, "is eating");
		philo->last_meal_time = get_time_in_ms();
		ft_usleep(philo->table->time_to_eat);
		pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
		pthread_mutex_unlock
			(&philo->table->forks[philo->id % philo->table->num_philosophers]);
		print_action(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep);
	}
  //return (NULL);
}
*/