/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:57:25 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/07 22:59:37 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/philo.h"

void    ft_usleep(int milliseconds)
{
      long    start_time;

      start_time = get_time_in_ms();
      while((get_time_in_ms() -start_time) < milliseconds)
            usleep(500);
}