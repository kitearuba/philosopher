/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/20 19:39:58 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void    cleanup_simulation(t_table *table)
{
      int      i;

      i = 0;
      // destroy all forks(1 pero philo)while (i < table->num_philo)
      while (i < table->num_philo)
      {
              pthread_mutex_destroy(&table->forks[i]);
              i++;
      }
      // Destroy other shared mutexes
      pthread_mutex_destroy(&table->print_lock);
      pthread_mutex_destroy(&table->death_lock);
      free(table->forks);
      free(table->philosophers);
}