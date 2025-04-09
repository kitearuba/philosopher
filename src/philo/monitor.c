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

void    *monitor_death(void *arg)
{
      t_table	*table;
      int		i;

      table = (t_table *)arg;
      while (1)
      {
              i = 0;
              while (i < table->num_philo)
              {
                    PM_LOCK(table->death_lock);
                    if (get_time_in_ms() - table->philosophers[i].last_meal_time > table->time_to_die)
                    {
                          // Print that the philosopher died
                          print_action(&table->philosophers[i], "died");
                          table->someone_died = 1;
                          PM_UNLOCK(table->death_lock);
                          return (NULL); // Exit the monitor
                    }
                    PM_UNLOCK(table->death_lock);
                    i++;
              }
              usleep(1000);
      }
      return (NULL);
}