/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/06/24 10:25:01 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static const char	*get_state_message(t_state state)
{
	if (state == STATE_EATING)
		return ("is eating");
	if (state == STATE_SLEEPING)
		return ("is sleeping");
	if (state == STATE_THINKING)
		return ("is thinking");
	if (state == STATE_TAKEN_FORK)
		return ("has taken a fork");
	if (state == STATE_DIED)
		return ("dies");
	return ("");
}

/**
 * @brief Maps action message to its corresponding color.
 *
 * @param message The action message (e.g., "is eating").
 * @return The ANSI color string.

static const char	*get_state_color(t_state state)
{
	if (state == STATE_EATING)
		return (GREEN);
	if (state == STATE_SLEEPING)
		return (CYAN);
	if (state == STATE_THINKING)
		return (BLUE);
	if (state == STATE_DIED)
		return (RED);
	return (RESET);
}
*/
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
void	print_action(t_philosophers *philo, t_state state)
{
	long		timestamp;
	const char	*message;
    t_table    *t;
	//const char	*color;

	t = philo->table;
	pthread_mutex_lock(&t->simulation_lock);
	if (t->simulation_ended && state != STATE_DIED)
	{
		pthread_mutex_unlock(&t->simulation_lock);
		return ;
	}
	pthread_mutex_unlock(&t->simulation_lock);
	pthread_mutex_lock(&t->print_lock);
	pthread_mutex_lock(&t->simulation_lock);
	if (t->simulation_ended &&  state != STATE_DIED)
	{
		pthread_mutex_unlock(&t->simulation_lock);
		pthread_mutex_unlock(&t->print_lock);
		return ;
	}
	pthread_mutex_unlock(&t->simulation_lock);
	timestamp = get_time_in_ms() - t->start_time;
	message = get_state_message(state);
/*	color = get_state_color(state);
	if (philo->table->log_colored)
		printf("%ld %s%d%s %s%s%s\n", timestamp, YELLOW, philo->id,
			RESET, color, message, RESET);
	else
		printf("%ld %d %s\n", timestamp, philo->id, message);
*/
	printf("%ld %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&t->print_lock);
}

/**
 * @brief Prints how many times each philosopher has eaten.
 *
 * This function is called at the end of the simulation to provide a summary.
 * It loops through all philosophers and reports their meal count.
 *
 * @param table Pointer to the shared simulation data.

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
*/