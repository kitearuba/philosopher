/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 22:12:46 by chrrodri          #+#    #+#             */
/*   Updated: 2025/09/14 22:13:36 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Lock forks in a deadlock-safe order.
 */
static void	handle_forking(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->table->num_philo;
	if (philo->id % 2 == 0)
	{
		lock_fork(philo, right);
		if (is_simulation_ended(philo->table))
		{
			unlock_forks(philo);
			return ;
		}
		lock_fork(philo, left);
	}
	else
	{
		lock_fork(philo, left);
		if (is_simulation_ended(philo->table))
		{
			unlock_forks(philo);
			return ;
		}
		lock_fork(philo, right);
	}
}

/**
 * @brief If max_meals set, mark fed & bump total_fed; end sim if all fed.
 */
static void	handle_meal_tracking(t_philo *philo)
{
	int	eaten;
	int	all_fed_now;

	all_fed_now = 0;
	if (philo->table->max_meals <= 0)
		return ;
	pthread_mutex_lock(&philo->state_lock);
	eaten = philo->meals_eaten;
	pthread_mutex_unlock(&philo->state_lock);
	pthread_mutex_lock(&philo->table->fed_lock);
	if (!philo->is_fed && eaten >= philo->table->max_meals)
	{
		philo->is_fed = 1;
		philo->table->total_fed++;
		if (philo->table->total_fed >= philo->table->num_philo)
			all_fed_now = 1;
	}
	pthread_mutex_unlock(&philo->table->fed_lock);
	if (all_fed_now)
		end_simulation_all_fed(philo->table);
}

/**
 * @brief Eat phase: log, update last_meal_time & meals_eaten, sleep eat time.
 */
static void	do_eat(t_philo *philo)
{
	print_action(philo, state_eating);
	pthread_mutex_lock(&philo->state_lock);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->state_lock);
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->state_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->state_lock);
	handle_meal_tracking(philo);
}

/**
 * @brief Sleep and optional tiny pad when num_philo is odd; then think.
 */
static void	do_sleep_pad_and_think(t_philo *philo)
{
	int	pad;

	print_action(philo, state_sleeping);
	ft_usleep(philo->table->time_to_sleep, philo->table);
	if ((philo->table->num_philo % 2) == 1)
	{
		pad = philo->table->time_to_eat - philo->table->time_to_sleep + 1;
		if (pad < 1)
			pad = 1;
		ft_usleep(pad, philo->table);
	}
	print_action(philo, state_thinking);
}

/**
 * @brief One full cycle: forks → eat → release → sleep/pad → think.
 */
void	do_cycle(t_philo *philo)
{
	if (is_simulation_ended(philo->table))
		return ;
	handle_forking(philo);
	if (is_simulation_ended(philo->table))
	{
		unlock_forks(philo);
		return ;
	}
	do_eat(philo);
	unlock_forks(philo);
	if (is_simulation_ended(philo->table))
		return ;
	do_sleep_pad_and_think(philo);
}
