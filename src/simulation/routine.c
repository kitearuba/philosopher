/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/07 22:56:05 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void *one_philo(t_philosophers *philo) {
  PM_LOCK(philo->table->forks[0]);
  print_action(philo, "has taken a fork");
  while (1) {
    PM_LOCK(philo->table->death_lock);
    if (philo->table->someone_died) {
      PM_UNLOCK(philo->table->death_lock);
      break;
    }
    PM_UNLOCK(philo->table->death_lock);
    usleep(100);
  }
  PM_UNLOCK(philo->table->forks[0]);
  return (NULL);
}

static int death_check(t_philosophers *philo) {
  PM_LOCK(philo->table->death_lock);
  if (philo->table->someone_died) {
    PM_UNLOCK(philo->table->death_lock);
    return (1);
  }
  PM_UNLOCK(philo->table->death_lock);
  return (0);
}

static void handle_forking(t_philosophers *philo) {
  if (philo->id % 2 == 0) {
    PM_LOCK(philo->table->forks[philo->id % philo->table->num_philo]);
    if (death_check(philo))
      return;
    print_action(philo, "has taken a fork");
    PM_LOCK(philo->table->forks[philo->id - 1]);
    if (death_check(philo))
      return;
    print_action(philo, "has taken a fork");
  } else {
    PM_LOCK(philo->table->forks[philo->id - 1]);
    if (death_check(philo))
      return;
    print_action(philo, "has taken a fork");
    if (death_check(philo))
      return;
    PM_LOCK(philo->table->forks[philo->id % philo->table->num_philo]);
    if (death_check(philo))
      return;
    print_action(philo, "has taken a fork");
  }
}

static void do_cycle(t_philosophers *philo) {
  print_action(philo, "is eating");
  if (death_check(philo))
    return;
  philo->last_meal_time = get_time_in_ms();
  ft_usleep(philo->table->time_to_eat);
  philo->meals_eaten++;
  if (philo->table->max_meals > 0 &&
      philo->meals_eaten == philo->table->max_meals) {
    PM_LOCK(philo->table->fed_lock);
    philo->table->total_fed++;
    PM_UNLOCK(philo->table->fed_lock);
    if (death_check(philo))
      return;
  }
  PM_UNLOCK(philo->table->forks[philo->id - 1]);
  PM_UNLOCK(philo->table->forks[philo->id % philo->table->num_philo]);
  if (death_check(philo))
    return;
  print_action(philo, "is sleeping");
  ft_usleep(philo->table->time_to_sleep);
}

void *philo_routine(void *arg) {
  t_philosophers *philo;

  philo = (t_philosophers *)arg;
  // one philo edge case
  if (philo->table->num_philo == 1)
    return (one_philo(philo));
  while (1) {
    if (death_check(philo))
      break;
    handle_forking(philo);
    if (death_check(philo))
      break;
    do_cycle(philo);
    if (death_check(philo))
      break;
  }
  return (NULL);
}