/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/07 22:56:05 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	*one_philo(t_philosophers *philo)
{
	PM_LOCK(philo->table->forks[0]);
	print_action(philo, "has taken a fork");
	while (!is_simulation_ended(philo->table))
	usleep(100);
/*
	while (1)
	{
		PM_LOCK(philo->table->death_lock);
		if (philo->table->someone_died)
		{
			PM_UNLOCK(philo->table->death_lock);
			break;
		}
		PM_UNLOCK(philo->table->death_lock);
		usleep(100);
	}
 */
	PM_UNLOCK(philo->table->forks[0]);
	return (NULL);
}

static void	unlock_forks(t_philosophers *philo)
{
	PM_UNLOCK(philo->table->forks[philo->id - 1]);
	PM_UNLOCK(philo->table->forks[philo->id % philo->table->num_philo]);
}
/*
static int	check_should_exit(t_philosophers *philo)
{
	PM_LOCK(philo->table->death_lock);
	if (philo->table->someone_died)
	{
		PM_UNLOCK(philo->table->death_lock);
		return (1);
	}
	PM_UNLOCK(philo->table->death_lock);
	PM_LOCK(philo->table->fed_lock);
	if (philo->table->total_fed >= philo->table->num_philo)
	{
		PM_LOCK(philo->table->death_lock);
		philo->table->someone_died = 1;
		PM_UNLOCK(philo->table->death_lock);
		PM_UNLOCK(philo->table->fed_lock);
		return (1);
	}
	PM_UNLOCK(philo->table->fed_lock);
	return (0);
}
*/

static void	handle_forking(t_philosophers *philo)
{
	int left;
	int right;

	left = philo->id - 1;
	right = philo->id % philo->table->num_philo;
	if (philo->id % 2 == 0)
	{
		PM_LOCK(philo->table->forks[right]);
		if (is_simulation_ended(philo->table))
			return (unlock_forks(philo), (void)0);
		print_action(philo, "has taken a fork");
		PM_LOCK(philo->table->forks[left]);
		if (is_simulation_ended(philo->table))
			return (unlock_forks(philo), (void)0);
		print_action(philo, "has taken a fork");
	}
	else
	{
		PM_LOCK(philo->table->forks[left]);
		if (is_simulation_ended(philo->table))
			return (unlock_forks(philo), (void)0);
		print_action(philo, "has taken a fork");
		PM_LOCK(philo->table->forks[right]);
		if (is_simulation_ended(philo->table))
			return (unlock_forks(philo), (void)0);
		print_action(philo, "has taken a fork");
	}
}

static void	do_cycle(t_philosophers *philo)
{
	if (is_simulation_ended(philo->table))
		return (unlock_forks(philo), (void)0);
	print_action(philo, "is eating");
	philo->last_meal_time = get_time_in_ms();
	ft_usleep(philo->table->time_to_eat);
	philo->meals_eaten++;
	if (philo->table->max_meals > 0
		&& philo->meals_eaten == philo->table->max_meals)
	{
		PM_LOCK(philo->table->fed_lock);
		philo->table->total_fed++;
		PM_UNLOCK(philo->table->fed_lock);
	}
	unlock_forks(philo);
	if (is_simulation_ended(philo->table))
		return;
	print_action(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
	if (is_simulation_ended(philo->table))
		return;
	print_action(philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	if (philo->table->num_philo == 1)
		return (one_philo(philo));
    while (!is_simulation_ended(philo->table))
	{
    	handle_forking(philo);
    	do_cycle(philo);
    }
/*
	while (1)
	{
		if (check_should_exit(philo))
			break;
		handle_forking(philo);
		if (check_should_exit(philo))
			break;
		do_cycle(philo);
		if (check_should_exit(philo))
			break;
	}
*/
	return (NULL);
}
