/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/06/24 22:55:00 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Map enum state to message.
 */
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
 * @brief Print a log line if the simulation hasn't ended (except death).
 *        Double-checks the end-flag both before and after taking print_lock
 *        to avoid interleaving after an end event.
 */
void	print_action(t_philosophers *philo, t_state state)
{
	long		timestamp;
	const char	*message;
	t_table		*t;

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
	if (t->simulation_ended && state != STATE_DIED)
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