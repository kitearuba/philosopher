/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/07 22:57:05 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	philo_routine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	while (1)
	{
		think(philo);
		eat(philo);
		sleep_philo(philo);
	}
  //return (NULL);
}
