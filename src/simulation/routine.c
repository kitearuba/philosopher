/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/05/17 17:27:19 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

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
 * @brief Tracks meal completion and updates total_fed if needed.
 *
 * If max_meals is enabled and the philosopher has eaten enough,
 * this function marks the philosopher as fed and increments the
 * shared total_fed counter (thread-safe with mutex).
 *
 * @param philo Pointer to the philosopher structure.
 */
static void	handle_meal_tracking(t_philosophers *philo)
{
	if (philo->table->max_meals <= 0)
		return ;
	pthread_mutex_lock(&philo->table->fed_lock);
	if (!philo->is_fed && philo->meals_eaten >= philo->table->max_meals)
	{
		philo->is_fed = 1;
		philo->table->total_fed++;
	}
	pthread_mutex_unlock(&philo->table->fed_lock);
}

/**
 * @brief Executes a complete eat-sleep-think cycle for a philosopher.
 *
 * Performs eating (updates timestamp and meal count), runs meal tracking,
 * and handles sleeping and thinking — with simulation checks at each stage.
 * Forks are unlocked after eating, and actions are logged conditionally.
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
    print_action(philo, STATE_EATING);
    philo->last_meal_time = get_time_in_ms();
	ft_usleep(philo->table->time_to_eat, philo->table);
	philo->meals_eaten++;
	handle_meal_tracking(philo);
	unlock_forks(philo);
	if (is_simulation_ended(philo->table))
		return ;
    print_action(philo, STATE_SLEEPING);
	ft_usleep(philo->table->time_to_sleep, philo->table);
	if (is_simulation_ended(philo->table))
		return ;
    print_action(philo, STATE_THINKING);

}

/**
 * @brief Main routine executed by each philosopher thread.
 *
 * If there is only one philosopher, they pick up one fork and wait
 * (never eating). For multiple philosophers, it continuously loops:
 * - acquiring forks in deadlock-safe order
 * - performing the eat-sleep-think cycle
 * until the simulation is marked as ended by the monitor.
 *
 * @param arg Pointer to the philosopher structure.
 * @return NULL when routine exits.
 */
void	*philo_routine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	if (philo->table->num_philo == 1)
	{
		pthread_mutex_lock(&philo->table->forks[0]);
	    print_action(philo, STATE_TAKEN_FORK);
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
