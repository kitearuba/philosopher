/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/09/14 22:11:56 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initial staggering to reduce immediate contention.
 */
static void	initial_stagger(t_philo *philo)
{
	if (philo->table->num_philo <= 1)
		return ;
	if ((philo->table->num_philo % 2) == 1)
	{
		if ((philo->id % 2) == 0)
			ft_usleep(philo->table->time_to_eat, philo->table);
	}
	else if ((philo->id % 2) == 0)
		ft_usleep(philo->table->time_to_eat / 2, philo->table);
}

/**
 * @brief Philosopher thread entry; loop until end flag flips.
 */
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->num_philo == 1)
	{
		pthread_mutex_lock(&philo->table->forks[0]);
		print_action(philo, state_taken_fork);
		while (!is_simulation_ended(philo->table))
			ft_usleep(1, philo->table);
		pthread_mutex_unlock(&philo->table->forks[0]);
		return (NULL);
	}
	initial_stagger(philo);
	while (!is_simulation_ended(philo->table))
		do_cycle(philo);
	return (NULL);
}
