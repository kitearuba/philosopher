/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/21 22:47:39 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Unlocks both forks held by the philosopher.
 *
 * Unlocks the left and right forks of the philosopher.
 *
 * @param philo Pointer to the philosopher structure.
 */
static void unlock_forks(t_philosophers *philo) {
  pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
  pthread_mutex_unlock(
      &philo->table->forks[philo->id % philo->table->num_philo]);
}

static void lock_fork(t_philosophers *philo, int fork_index) {
  pthread_mutex_lock(&philo->table->forks[fork_index]);
  if (is_simulation_ended(philo->table))
    unlock_forks(philo);
  else
    print_action(philo, "has taken a fork");
}

/**
 * @brief Handles fork acquisition in a deadlock-avoidance pattern.
 *
 * Even philosophers pick up the right fork first, then left.
 * Odd philosophers do the reverse. Prevents deadlocks.
 *
 * @param philo Pointer to the philosopher structure.
 */
static void handle_forking(t_philosophers *philo) {
  int left;
  int right;

  left = philo->id - 1;
  right = philo->id % philo->table->num_philo;
  if (philo->id % 2 == 0) {
    lock_fork(philo, right);
    if (is_simulation_ended(philo->table))
      lock_fork(philo, left);
  } else {
    lock_fork(philo, left);
    if (is_simulation_ended(philo->table))
      lock_fork(philo, right);
  }
}

/**
 * @brief Performs eating, sleeping, and thinking cycle for a philosopher.
 *
 * Updates last meal time, increments meals eaten,
 * and optionally updates the total fed counter if the max meal count is reached.
 *
 * @param philo Pointer to the philosopher structure.
 */
static void do_cycle(t_philosophers *philo)
{
  if (is_simulation_ended(philo->table))
    return (unlock_forks(philo), (void)0);
  print_action(philo, "is eating");
  philo->last_meal_time = get_time_in_ms();
  ft_usleep(philo->table->time_to_eat);
  philo->meals_eaten++;
  if (philo->table->max_meals > 0 && philo->meals_eaten == philo->table->
      max_meals) {
    pthread_mutex_lock(&philo->table->fed_lock);
    if (philo->meals_eaten == philo->table->max_meals)
      philo->table->total_fed++;
    pthread_mutex_unlock(&philo->table->fed_lock);
  }
  unlock_forks(philo);
  if (is_simulation_ended(philo->table))
    return;
  print_action(philo, "is sleeping");
  ft_usleep(philo->table->time_to_sleep);
  if (is_simulation_ended(philo->table))
    return;
  print_action(philo, "is thinking");
}

/**
 * @brief Main thread routine for each philosopher.
 *
 * Alternates between acquiring forks, eating, sleeping, and thinking
 * until the simulation ends. Handles the one-philosopher case.
 *
 * @param arg Pointer to the philosopher structure (cast from void*).
 * @return NULL.
 */
void *philo_routine(void *arg)
{
  t_philosophers *philo;

  philo = (t_philosophers *)arg;
  if (philo->table->num_philo == 1) {
    pthread_mutex_lock(&philo->table->forks[0]);
    print_action(philo, "has taken a fork");
    while (!is_simulation_ended(philo->table))
      usleep(100);
    pthread_mutex_unlock(&philo->table->forks[0]);
    return (NULL);
  }
  while (!is_simulation_ended(philo->table)) {
    handle_forking(philo);
    do_cycle(philo);
  }
  return (NULL);
}
