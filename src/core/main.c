/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/07 23:07:49 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void start_simulation(t_table *table) {
  int i;

  i = 0;
  table->start_time = get_time_in_ms();
  while (i < table->num_philo) {
    table->philosophers[i].id = i + 1;
    table->philosophers[i].last_meal_time = table->start_time;
    table->philosophers[i].table = table;
    pthread_create(&table->philosophers[i].thread, NULL, philo_routine,
                   &table->philosophers[i]);
    i++;
  }
}

int main(int argc, char **argv) {
  t_table *table;
  pthread_t monitor;
  int i;

  table = malloc(sizeof(t_table));
  if (!table)
    return (1);
  i = 0;
  if (init_simulation(table, argc, argv))
    return (1);
  start_simulation(table);
  pthread_create(&monitor, NULL, monitor_death, table);
  // ⏳ Wait for the monitor to finish (someone died or everyone ate)
  pthread_join(monitor, NULL);
  // Wait for all philosophers to finish
  while (i < table->num_philo) {
    pthread_join(table->philosophers[i].thread, NULL);
    i++;
  }
  cleanup_simulation(table);
  free(table);
  return (0);
}
