/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 22:37:30 by chrrodri          #+#    #+#             */
/*   Updated: 2025/05/10 22:38:26 by chrrodri         ###   ########.fr       */
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
void	unlock_forks(t_philosophers *philo)
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
void	lock_fork(t_philosophers *philo, int fork_index)
{
	pthread_mutex_lock(&philo->table->forks[fork_index]);
	if (!is_simulation_ended(philo->table))
		print_action(philo, "has taken a fork");
}
