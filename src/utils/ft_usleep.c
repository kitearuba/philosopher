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

#include "philo.h"

/*
** Sleep approximately `milliseconds`, but wake early if the simulation ends.
** Uses small adaptive usleep slices to stay responsive to the end flag.
*/
void    ft_usleep(int milliseconds, t_table *table)
{
    long    end;
    long    now;
    long    remaining;
    int     slice_us;

    end = get_time_in_ms() + milliseconds;
    while (!is_simulation_ended(table))
    {
        now = get_time_in_ms();
        remaining = end - now;
        if (remaining <= 0)
            break;
        if (remaining > 5)
            slice_us = 500;
        else
            slice_us = 100;
		usleep(slice_us);
	}
}
