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

#include "../../include/philo.h"

/**
 * Locks forks in an order that reduces deadlocks.
 * Even IDs: right then left. Odd IDs: left then right.
 */
static void	handle_forking(t_philosophers *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->table->num_philo;

	if (is_simulation_ended(philo->table))
		return;

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
		/* FIX: bail only if the simulation ENDED (the old code had !ended) */
		if (is_simulation_ended(philo->table))
		{
			unlock_forks(philo);
			return ;
		}
		lock_fork(philo, right);
	}
}

/* After finishing a meal, if max_meals > 0 and this philo reached it,
 * mark as fed and increment total_fed. If that makes everyone fed,
 * flip simulation_ended immediately (like a death), so printing stops at once.
 */
static void handle_meal_tracking(t_philosophers *philo)
{
    int eaten;
    int all_fed_now = 0;

    if (philo->table->max_meals <= 0)
        return;

    /* Read meals_eaten under state lock */
    pthread_mutex_lock(&philo->state_lock);
    eaten = philo->meals_eaten;
    pthread_mutex_unlock(&philo->state_lock);

    /* Update fed counters under fed_lock */
    pthread_mutex_lock(&philo->table->fed_lock);
    if (!philo->is_fed && eaten >= philo->table->max_meals)
    {
        philo->is_fed = 1;
        philo->table->total_fed++;
        if (philo->table->total_fed >= philo->table->num_philo)
            all_fed_now = 1;
    }
    pthread_mutex_unlock(&philo->table->fed_lock);

    /* If we just reached "everyone fed", end now (no print). */
    if (all_fed_now)
        end_simulation_all_fed(philo->table);
}


/**
 * One eat-sleep-think cycle with end checks between phases.
 */
static void	do_cycle(t_philosophers *philo)
{
	if (is_simulation_ended(philo->table))
	{
		unlock_forks(philo);
		return ;
	}
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
        int pad = philo->table->time_to_eat - philo->table->time_to_sleep + 1;
        if (pad < 1)
            pad = 1; /* 1ms is enough to break symmetry */
        ft_usleep(pad, philo->table);
    }
	print_action(philo, STATE_THINKING);
}

/**
 * Thread entry: loop until the monitor flips the end flag.
 * Never gate by max_meals here; only end-flag matters.
 */
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
            /* Odd N: even IDs wait a full eat time */
            if ((philo->id % 2) == 0)
                ft_usleep(philo->table->time_to_eat, philo->table);
        }
        else
        {
            /* Even N: even IDs wait half eat time */
            if ((philo->id % 2) == 0)
                ft_usleep(philo->table->time_to_eat / 2, philo->table);
        }
    }
	while (!is_simulation_ended(philo->table))
	{
		handle_forking(philo);
		do_cycle(philo);
	}
	return (NULL);
}