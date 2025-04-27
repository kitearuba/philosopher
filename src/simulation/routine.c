/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/24 18:18:00 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Locks a fork for a philosopher and prints the action if simulation is active.
 *
 * If the simulation has ended, unlocks the forks instead.
 *
 * @param philo Pointer to the philosopher structure.
 * @param fork_index Index of the fork to lock.
 */
static void	unlock_forks(t_philosophers *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->table->forks[
		philo->id % philo->table->num_philo]);
}

/**
 * @brief Handles fork locking order based on philosopher ID.
 *
 * Even IDs pick up the right fork first, odd IDs pick up the left fork first.
 * This reduces the risk of deadlocks.
 *
 * @param philo Pointer to the philosopher structure.
 */
static void	lock_fork(t_philosophers *philo, int fork_index)
{
	pthread_mutex_lock(&philo->table->forks[fork_index]);
	if (is_simulation_ended(philo->table))
		unlock_forks(philo);
	else
		print_action(philo, "has taken a fork");
}

/**
 * @brief Handles fork locking order based on philosopher ID.
 *
 * Even IDs pick up the right fork first, odd IDs pick up the left fork first.
 * This reduces the risk of deadlocks.
 *
 * @param philo Pointer to the philosopher structure.
 */
static void	handle_forking(t_philosophers *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->table->num_philo;
	if (philo->id % 2 == 0)
	{
		lock_fork(philo, right);
		if (!is_simulation_ended(philo->table))
			lock_fork(philo, left);
	}
	else
	{
		lock_fork(philo, left);
		if (!is_simulation_ended(philo->table))
			lock_fork(philo, right);
	}
}

/**
 * @brief Executes one full cycle of eating, sleeping, and thinking.
 *
 * Handles fork unlocking, meal counting, sleeping, and thinking actions.
 *
 * @param philo Pointer to the philosopher structure.
 */
static void	do_cycle(t_philosophers *philo)
{
	if (is_simulation_ended(philo->table))
	{
		unlock_forks(philo);
		return ;
	}
	print_action(philo, "is eating");
	philo->last_meal_time = get_time_in_ms();
	ft_usleep(philo->table->time_to_eat);
	philo->meals_eaten++;
	if (philo->table->max_meals > 0
		&& philo->meals_eaten == philo->table->max_meals)
	{
		pthread_mutex_lock(&philo->table->fed_lock);
		if (philo->meals_eaten == philo->table->max_meals)
			philo->table->total_fed++;
		pthread_mutex_unlock(&philo->table->fed_lock);
	}
	unlock_forks(philo);
	if (is_simulation_ended(philo->table))
		return ;
	print_action(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
	if (is_simulation_ended(philo->table))
		return ;
	print_action(philo, "is thinking");
}

/**
 * @brief Routine executed by each philosopher thread.
 *
 * Handles the special case for a single philosopher, and otherwise
 * continuously repeats the eating-sleeping-thinking cycle until the simulation
 * ends.
 *
 * @param arg Pointer to the philosopher structure.
 * @return NULL when routine finishes.
 */
void	*philo_routine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	if (philo->table->num_philo == 1)
	{
		pthread_mutex_lock(&philo->table->forks[0]);
		print_action(philo, "has taken a fork");
		while (!is_simulation_ended(philo->table))
			usleep(100);
		pthread_mutex_unlock(&philo->table->forks[0]);
		return (NULL);
	}
	while (!is_simulation_ended(philo->table))
	{
		handle_forking(philo);
		do_cycle(philo);
	}
	return (NULL);
}
