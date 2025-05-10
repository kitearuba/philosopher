/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:57:25 by chrrodri          #+#    #+#             */
/*   Updated: 2025/05/10 21:58:11 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Sleeps for a given number of milliseconds, with early exit if 
 * simulation ends.
 *
 * This function wraps around `usleep` in a loop to achieve more accurate 
 * delays, especially in simulations with small timing margins. It checks both 
 * the elapsed time and whether the simulation has ended, to avoid unnecessary 
 * waiting after a philosopher has died or the simulation is marked complete.
 *
 * @param milliseconds Duration to sleep, in milliseconds.
 * @param table Pointer to the shared simulation table (used to check stop 
 * condition).
 */
void	ft_usleep(int milliseconds, t_table *table)
{
	long	start_time;

	start_time = get_time_in_ms();
	while ((get_time_in_ms() - start_time) < milliseconds)
	{
		if (is_simulation_ended(table))
			break ;
		usleep(500);
	}
}
