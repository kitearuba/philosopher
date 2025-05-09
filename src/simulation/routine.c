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
 * @brief Unlocks both forks held by a philosopher.
 *
 * This function releases the mutexes for the left and right forks
 * associated with the given philosopher. It is called after eating
 * or when the simulation ends prematurely.
 *
 * @param philo Pointer to the philosopher structure.
 */
static void	unlock_forks(t_philosophers *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->table->forks[
		philo->id % philo->table->num_philo]);
}

/**
 * @brief Locks a specific fork and logs the action.
 *
 * Locks the fork at the given index. If the simulation has not ended,
 * prints a log message indicating the fork has been taken.
 *
 * @param philo Pointer to the philosopher structure.
 * @param fork_index Index of the fork to lock.
 */
static void	lock_fork(t_philosophers *philo, int fork_index)
{
	pthread_mutex_lock(&philo->table->forks[fork_index]);
	if (!is_simulation_ended(philo->table))
		print_action(philo, "has taken a fork");
}

/**
 * @brief Locks forks in an order that reduces deadlocks.
 *
 * Even-numbered philosophers pick up the right fork first,
 * while odd-numbered philosophers pick up the left fork first.
 * This strategy helps avoid circular wait and deadlock scenarios.
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
 * The philosopher eats (locking both forks), increments meal counters,
 * sleeps, and then thinks — unless the simulation ends in between.
 * Forks are unlocked after eating. Simulation checks are performed
 * throughout to allow early termination.
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
	ft_usleep(philo->table->time_to_eat, philo->table);
	philo->meals_eaten++;
	if (philo->table->max_meals > 0)
	{
		pthread_mutex_lock(&philo->table->fed_lock);
	    if (philo->meals_eaten == philo->table->max_meals)
	    {
	        philo->table->total_fed++;
	        if (philo->table->total_fed == philo->table->num_philo)
	            set_simulation_end(philo->table);
	    }
		pthread_mutex_unlock(&philo->table->fed_lock);
	}
	unlock_forks(philo);
	if (is_simulation_ended(philo->table))
		return ;
	print_action(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep, philo->table);
	if (is_simulation_ended(philo->table))
		return ;
	print_action(philo, "is thinking");
}

/**
 * @brief Routine executed by each philosopher thread.
 *
 * If only one philosopher exists, waits holding one fork (and never eats).
 * Otherwise, enters a loop of:
 * - locking forks in safe order
 * - performing the eating/sleeping/thinking cycle
 * This loop runs until the simulation is marked as ended.
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
		    ft_usleep(1, philo->table);
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
