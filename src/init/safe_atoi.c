/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/21 21:58:43 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Safely converts a string to an integer, with error checking.
 *
 * Handles whitespace, non-digit characters, and integer overflow. If the input
 * is invalid or overflows, and returns 0.
 *
 * @param str The string to convert.
 * @return The converted integer, or 0 if an error occurred.
 */
int	safe_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (!str || !str[i])
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (!str[i])
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (0);
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return ((int)result);
}
