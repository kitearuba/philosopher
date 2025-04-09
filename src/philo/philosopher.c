/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/07 22:57:05 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	philo_routine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
    while (1)
    {
        // 🧠 Step 1: Think
        print_action(philo, "is thinking");

        // 🍴 Step 2: Take Forks
        PM_LOCK(philo->table->forks[philo->id - 1]); // Lock left fork
        print_action(philo, "has taken a fork");

        PM_LOCK(philo->table->forks[philo->id % philo->table->num_philo]); // Lock right fork
        print_action(philo, "has taken a fork");

        // 🍝 Step 3: Eat
        print_action(philo, "is eating");
        philo->last_meal_time = get_time_in_ms(); // Update last meal timestamp
        ft_usleep(philo->table->time_to_eat);

        // 🔓 Step 4: Release Forks
        PM_UNLOCK(philo->table->forks[philo->id - 1]); // Unlock left fork
        PM_UNLOCK(philo->table->forks[philo->id % philo->table->num_philo]); // Unlock right fork

        // 😴 Step 5: Sleep
        print_action(philo, "is sleeping");
        ft_usleep(philo->table->time_to_sleep);
    }
    //return (NULL);
}