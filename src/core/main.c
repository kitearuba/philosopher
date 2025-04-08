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
  while (i < table->num_philosophers) {
    table->philosophers[i].id = i + 1;
    table->philosophers[i].last_meal_time = get_time_in_ms();
    table->philosophers[i].table = table;
    pthread_create(&table->philosophers[i].thread, NULL, philosopher_routine,
                   &table->philosophers[i]);
  }
  i = 0;
  while (i < table->num_philosophers)
    pthread_join(table->philosophers[i].thread, NULL);
}


int main(int argc, char **argv) {
  t_table table;

  if (init_simulation(&table, argc, argv))
    return (1);
  start_simulation(&table);
  return (0);
}
