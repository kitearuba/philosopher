/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/06/24 10:23:46 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** handle_forking: lock forks in an order that reduces deadlock. */
static void	handle_forking(t_philosophers *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->table->num_philo;
	if (is_simulation_ended(philo->table))
		return ;
	if (philo->id % 2 == 0)
	{
		lock_fork(philo, right);
		if (is_simulation_ended(philo->table))
			return (unlock_forks(philo));
		lock_fork(philo, left);
	}
	else
	{
		lock_fork(philo, left);
		if (is_simulation_ended(philo->table))
			return (unlock_forks(philo));
		lock_fork(philo, right);
	}
}

/** handle_meal_tracking: mark fed & bump total_fed; end sim if all fed. */
static void	handle_meal_tracking(t_philosophers *philo)
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

/** do_cycle: eat → sleep → (optional pad) → think with end checks. */
static void	do_cycle(t_philosophers *philo)
{
	if (is_simulation_ended(philo->table))
		return (unlock_forks(philo));
	print_action(philo, STATE_EATING);
	pthread_mutex_lock(&philo->state_lock);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->state_lock);
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->state_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->state_lock);
	handle_meal_tracking(philo);
	unlock_forks(philo);
	if (is_simulation_ended(philo->table))
		return ;
	print_action(philo, STATE_SLEEPING);
	ft_usleep(philo->table->time_to_sleep, philo->table);
	if (is_simulation_ended(philo->table))
		return ;
	if ((philo->table->num_philo % 2) == 1)
	{
		int	pad;

		pad = philo->table->time_to_eat - philo->table->time_to_sleep + 1;
		if (pad < 1)
			pad = 1;
		ft_usleep(pad, philo->table);
	}
	print_action(philo, STATE_THINKING);
}

/** philo_routine: thread entry; loop until end flag flips. */
void	*philo_routine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	if (philo->table->num_philo == 1)
	{
		pthread_mutex_lock(&philo->table->forks[0]);
		print_action(philo, STATE_TAKEN_FORK);
		while (!is_simulation_ended(philo->table))
			ft_usleep(1, philo->table);
		pthread_mutex_unlock(&philo->table->forks[0]);
		return (NULL);
	}
	if (philo->table->num_philo > 1)
	{
		if ((philo->table->num_philo % 2) == 1)
		{
			if ((philo->id % 2) == 0)
				ft_usleep(philo->table->time_to_eat, philo->table);
		}
		else if ((philo->id % 2) == 0)
			ft_usleep(philo->table->time_to_eat / 2, philo->table);
	}
	while (!is_simulation_ended(philo->table))
	{
		handle_forking(philo);
		do_cycle(philo);
	}
	return (NULL);
}
