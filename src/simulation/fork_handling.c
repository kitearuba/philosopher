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

void lock_fork(t_philosophers *philo, int fork_index)
{
    int left  = philo->id - 1;
    int right = philo->id % philo->table->num_philo;

    pthread_mutex_lock(&philo->table->forks[fork_index]);
    if (fork_index == left)
        philo->has_left_fork = 1;      // NEW
    else if (fork_index == right)
        philo->has_right_fork = 1;     // NEW

    if (!is_simulation_ended(philo->table))
        print_action(philo, STATE_TAKEN_FORK);
}

void unlock_forks(t_philosophers *philo)
{
    int left  = philo->id - 1;
    int right = philo->id % philo->table->num_philo;

    if (philo->has_right_fork) {                           // NEW
        pthread_mutex_unlock(&philo->table->forks[right]);
        philo->has_right_fork = 0;
    }
    if (philo->has_left_fork) {                            // NEW
        pthread_mutex_unlock(&philo->table->forks[left]);
        philo->has_left_fork = 0;
    }
}
