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

#include "philo.h"

/** lock_fork: lock fork mutex and record which side we hold. */
void	lock_fork(t_philosophers *philo, int fork_index)
{
    int	left;
    int	right;

    left = philo->id - 1;
    right = philo->id % philo->table->num_philo;
    pthread_mutex_lock(&philo->table->forks[fork_index]);
    if (fork_index == left)
        philo->has_left_fork = 1;
    else if (fork_index == right)
        philo->has_right_fork = 1;
    if (!is_simulation_ended(philo->table))
        print_action(philo, STATE_TAKEN_FORK);
}

/** unlock_forks: unlock only forks we actually hold (TSAN-friendly). */
void	unlock_forks(t_philosophers *philo)
{
    int	left;
    int	right;

    left = philo->id - 1;
    right = philo->id % philo->table->num_philo;
    if (philo->has_right_fork)
    {
        pthread_mutex_unlock(&philo->table->forks[right]);
        philo->has_right_fork = 0;
    }
    if (philo->has_left_fork)
    {
        pthread_mutex_unlock(&philo->table->forks[left]);
        philo->has_left_fork = 0;
    }
}