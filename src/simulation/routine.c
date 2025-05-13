/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/05/10 23:12:26 by chrrodri         ###   ########.fr       */
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
 * @brief Handles the eating phase and meal tracking logic.
 *
 * Locks both forks, logs the eating action, updates the last meal timestamp,
 * sleeps for the eating duration, and increments the meals eaten count.
 * Also updates the total_fed counter if the philosopher has reached the
 * required number of meals. Forks are unlocked at the end.
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
 * @brief Executes a full philosopher cycle of eating, sleeping, and thinking.
 *
 * This function coordinates the philosopher’s routine by first checking
 * simulation status, then invoking the helper that handles eating and
 * meal tracking. If the simulation hasn’t ended, it proceeds with sleeping
 * and thinking phases.
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
    handle_meal_tracking(philo);
    unlock_forks(philo);
    if (is_simulation_ended(philo->table))
        return ;
    print_action(philo, "is sleeping");
    ft_usleep(philo->table->time_to_sleep, philo->table);
    if (!is_simulation_ended(philo->table))
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