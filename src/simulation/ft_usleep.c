/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:57:25 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/21 21:59:19 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Sleeps for a given amount of time in milliseconds.
 *
 * A wrapper around usleep that checks elapsed time in a loop,
 * ensuring more precise timing than a single usleep call.
 *
 * @param milliseconds Time to sleep in milliseconds.
 */
void	ft_usleep(int milliseconds)
{
	long	start_time;

	start_time = get_time_in_ms();
	while ((get_time_in_ms() - start_time) < milliseconds)
		usleep(500);
}
