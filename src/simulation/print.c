/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/20 19:39:58 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/philo.h"

/**
 * @brief Compares two strings (like strcmp).
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @return Difference between first unmatched characters, or 0 if equal.
 */
static int ft_strcmp(const char *s1, const char *s2) {
  while (*s1 && *s2) {
    if (*s1 != *s2)
      return ((unsigned char)*s1 - (unsigned char)*s2);
    s1++;
    s2++;
  }
  return ((unsigned char)*s1 - (unsigned char)*s2);
}

/**
 * @brief Prints a philosopher action with timestamp and optional color.
 *
 * Ensures printing is thread-safe. Skips printing if simulation has ended,
 * unless the action is "died".
 *
 * @param philo Pointer to the philosopher struct.
 * @param message Action message (e.g., "is eating", "died", etc.).
 */
void print_action(t_philosophers *philo, const char *message) {
  long timestamp;
  const char *color;

  if (is_simulation_ended(philo->table) && ft_strcmp(message, "died") != 0)
    return;
  color = RESET;
  if (!ft_strcmp(message, "is eating"))
    color = GREEN;
  else if (!ft_strcmp(message, "is sleeping"))
    color = CYAN;
  else if (!ft_strcmp(message, "is thinking"))
    color = BLUE;
  else
    if (!ft_strcmp(message, "died"))
      color = RED;
  pthread_mutex_lock(&philo->table->print_lock);
  timestamp = get_time_in_ms() - philo->table->start_time;
  if (philo->table->log_colored)
    printf("%ld %s%d%s %s%s%s\n", timestamp, YELLOW, philo->id, RESET, color,
           message, RESET);
  else
    printf("%ld %d %s\n", timestamp, philo->id, message);
  pthread_mutex_unlock(&philo->table->print_lock);
}

/**
 * @brief Prints how many times each philosopher has eaten.
 *
 * Called at the end of the simulation if philosopher count is low enough.
 *
 * @param table Pointer to the simulation table.
 */
void print_meal_summary(t_table *table) {
  int i;

  i = 0;
  printf("\nSimulation ended. Meal summary:\n");
  while (i < table->num_philo) {
    printf("Philosopher %d ate %d ", table->philosophers[i].id,
           table->philosophers[i].meals_eaten);
    if (table->philosophers[i].meals_eaten == 1)
      printf("time\n");
    else
      printf("times\n");
    i++;
  }
}
