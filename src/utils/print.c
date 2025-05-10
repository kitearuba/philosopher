/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/05/10 22:00:22 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Compares two strings for equality.
 *
 * Mimics the behavior of the standard strcmp function.
 * Compares each character in order and returns the difference
 * between the first pair of non-matching characters.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @return 0 if strings are equal, a non-zero integer otherwise.
 */
static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/**
 * @brief Maps action message to its corresponding color.
 *
 * @param message The action message (e.g., "is eating").
 * @return The ANSI color string.
 */
static const char	*message_to_color(const char *message)
{
	if (!ft_strcmp(message, "is eating"))
		return (GREEN);
	if (!ft_strcmp(message, "is sleeping"))
		return (CYAN);
	if (!ft_strcmp(message, "is thinking"))
		return (BLUE);
	if (!ft_strcmp(message, "died"))
		return (RED);
	return (RESET);
}

/**
 * @brief Prints a philosopher's current action with a timestamp and optional
 * color.
 *
 * This function locks the print mutex to safely output messages to the 
 * terminal.
 * It ensures that messages are only printed if the simulation is still running,
 * except for the "died" message, which must always be printed. Output is 
 * color-coded for better readability when log_colored is enabled.
 *
 * @param philo Pointer to the philosopher.
 * @param message The action message (e.g., "is eating", "died").
 */
void	print_action(t_philosophers *philo, const char *message)
{
	long		timestamp;
	const char	*color;

	if (is_simulation_ended(philo->table) && ft_strcmp(message, "died") != 0)
		return ;
	pthread_mutex_lock(&philo->table->print_lock);
	if (is_simulation_ended(philo->table) && ft_strcmp(message, "died") != 0)
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return ;
	}
	timestamp = get_time_in_ms() - philo->table->start_time;
	color = message_to_color(message);
	if (philo->table->log_colored)
		printf("%ld %s%d%s %s%s%s\n", timestamp, YELLOW, philo->id,
			RESET, color, message, RESET);
	else
		printf("%ld %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->table->print_lock);
}

/**
 * @brief Prints how many times each philosopher has eaten.
 *
 * This function is called at the end of the simulation to provide a summary.
 * It loops through all philosophers and reports their meal count.
 *
 * @param table Pointer to the shared simulation data.
 */
void	print_meal_summary(t_table *table)
{
	int	i;

	i = 0;
	printf("\nSimulation ended. Meal summary:\n");
	while (i < table->num_philo)
	{
		printf("Philosopher %d ate %d ", table->philosophers[i].id,
			table->philosophers[i].meals_eaten);
		if (table->philosophers[i].meals_eaten == 1)
			printf("time\n");
		else
			printf("times\n");
		i++;
	}
}
