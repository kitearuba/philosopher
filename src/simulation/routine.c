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

// static void *check_(t_philosophers *philo)

void *philo_routine(void *arg) {
  t_philosophers *philo;

  philo = (t_philosophers *)arg;
  if (philo->table->num_philo == 1)
    return (one_philo(philo));
  while (1) {

    PM_LOCK(philo->table->death_lock);
    if (philo->table->someone_died) {
      PM_UNLOCK(philo->table->death_lock);
      break; // Exit thread if someone died
    }
    PM_UNLOCK(philo->table->death_lock);
    print_action(philo, "is thinking");
    // Taking forks safely (even/odd strategy)
    if (philo->id % 2 == 0) {
      // Even: Take right fork first
      PM_LOCK(philo->table->forks[philo->id % philo->table->num_philo]);
      print_action(philo, "has taken a fork");

      PM_LOCK(philo->table->forks[philo->id - 1]);
      print_action(philo, "has taken a fork");
    } else {
      // Odd: Take left fork first
      PM_LOCK(philo->table->forks[philo->id - 1]);
      print_action(philo, "has taken a fork");
      PM_LOCK(philo->table->forks[philo->id % philo->table->num_philo]);
      print_action(philo, "has taken a fork");
    }
    //  Eating
    print_action(philo, "is eating");
    philo->last_meal_time = get_time_in_ms();
    ft_usleep(philo->table->time_to_eat);

    // meals limit check
    philo->meals_eaten++;
    if (philo->table->max_meals > 0 &&
        philo->meals_eaten == philo->table->max_meals) {
      PM_LOCK(philo->table->fed_lock);
      philo->table->total_fed++;
      PM_UNLOCK(philo->table->fed_lock);
    }
    // Releasing forks
    PM_UNLOCK(philo->table->forks[philo->id - 1]);
    PM_UNLOCK(philo->table->forks[philo->id % philo->table->num_philo]);

    // Sleeping
    print_action(philo, "is sleeping");
    ft_usleep(philo->table->time_to_sleep);
  }
  return (NULL);
}