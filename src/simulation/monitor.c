/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/09 22:52:30 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static int check_death(t_table *table, int i)
{
  long time;

  time = get_time_in_ms() - table->philosophers[i].last_meal_time;
  if (time > table->time_to_die) {
    print_action(&table->philosophers[i], "died");
    set_simulation_end(table);
    return (1);
  }
  return (0);
}

static int check_all_ate(t_table *table) {
  if (table->max_meals > 0) {
    if (table->total_fed >= table->num_philo)
    {
      set_simulation_end(table);
      return (1);
    }
  }
  return (0);
}

void *monitor_death(void *arg) {
  t_table *table;
  int i;

  table = (t_table *)arg;
  while (!is_simulation_ended(table))
  {
    i = 0;
    while (i < table->num_philo) {
      if (check_death(table, i))
        return (NULL);
      i++;
    }
    if (check_all_ate(table))
      return (NULL);
    usleep(1000);
  }
  return (NULL);
}