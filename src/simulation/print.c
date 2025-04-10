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

void    print_action(t_philosophers *philo, const char *message)
{
      long    timestamp;

      PM_LOCK(philo->table->print_lock);
      timestamp = get_time_in_ms() - philo->table->start_time;
      printf("%ld %d %s\n", timestamp, philo->id, message);
      PM_UNLOCK(philo->table->print_lock);
}