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

void    lock_fork(t_philosophers *philo, int fork_index)
{
    int left;
    int right;

    left = philo->id - 1;
    right = philo->id % philo->table->num_philo;
    pthread_mutex_lock(&philo->table->forks[fork_index]);
    pthread_mutex_lock(&philo->state_lock);
    if (fork_index == left)
        philo->has_left_fork = 1;
    else if (fork_index == right)
        philo->has_right_fork = 1;
    pthread_mutex_unlock(&philo->state_lock);
    if (!is_simulation_ended(philo->table))
        print_action(philo, STATE_TAKEN_FORK);
}

void    unlock_forks(t_philosophers *philo)
{
    int left;
    int right;
    int had_left;
    int had_right;

    left = philo->id - 1;
    right = philo->id % philo->table->num_philo;
    pthread_mutex_lock(&philo->state_lock);
    had_left = philo->has_left_fork;
    had_right = philo->has_right_fork;
    philo->has_left_fork = 0;
    philo->has_right_fork = 0;
    pthread_mutex_unlock(&philo->state_lock);
    if (had_right)
        pthread_mutex_unlock(&philo->table->forks[right]);
    if (had_left)
        pthread_mutex_unlock(&philo->table->forks[left]);
}
