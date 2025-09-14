/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/09/14 22:22:45 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Map enum state to message.
 */
static const char	*get_state_message(t_state state)
{
	if (state == state_eating)
		return ("is eating");
	if (state == state_sleeping)
		return ("is sleeping");
	if (state == state_thinking)
		return ("is thinking");
	if (state == state_taken_fork)
		return ("has taken a fork");
	if (state == state_died)
		return ("died");
	return ("");
}

/**
 * @brief Check end flag once (lightweight guard).
 */
static int	is_end_and_not_death(t_table *t, t_state s)
{
	int	ended;

	pthread_mutex_lock(&t->simulation_lock);
	ended = t->simulation_ended && (s != state_died);
	pthread_mutex_unlock(&t->simulation_lock);
	return (ended);
}

/**
 * @brief Print a log line if the simulation hasn't ended (except death).
 * Double-checks the end-flag before and after taking print_lock.
 */
void	print_action(t_philo *philo, t_state state)
{
	long		timestamp;
	const char	*msg;
	t_table		*t;

	t = philo->table;
	if (is_end_and_not_death(t, state))
		return ;
	pthread_mutex_lock(&t->print_lock);
	if (is_end_and_not_death(t, state))
	{
		pthread_mutex_unlock(&t->print_lock);
		return ;
	}
	timestamp = get_time_in_ms() - t->start_time;
	msg = get_state_message(state);
	printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&t->print_lock);
}
