/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/06 20:23:56 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void start_simulation(t_table *table) {
  int i;

  i = 0;
  while (i < table->num_philosophers) {
    table->philosophers[i].id = i + 1;
    table->philosophers[i].last_meal_time = get_time_ms();
    table->philosophers[i].table = table;
    pthread_create
  }
}
int	main(int argc, char **argv)
{

}
