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
    printf("%ld %d %s\n", timestamp, philo->id, message);
    pthread_mutex_unlock(&t->print_lock);
}