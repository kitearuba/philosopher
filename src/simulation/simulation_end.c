/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:02:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/13 22:56:05 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	is_simulation_ended(t_table *table)
{
  int	status;

  pthread_mutex_lock(&table->simulation_lock);
  status = table->simulation_ended;
  pthread_mutex_unlock(&table->simulation_lock);
  return (status);
}

void	set_simulation_end(t_table *table)
{
  pthread_mutex_lock(&table->simulation_lock);
  table->simulation_ended = 1;
  pthread_mutex_unlock(&table->simulation_lock);
}

