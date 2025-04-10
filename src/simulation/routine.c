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
    PM_UNLOCK(philo->table->forks[0]);
    return (NULL);
}

PM_LOCK(philo->table->death_lock);
	    if (philo->table->someone_died)
	    {
		    PM_UNLOCK(philo->table->death_lock);
		    break; // Exit thread if someone died
	    }
	    PM_UNLOCK(philo->table->death_lock);
		// 🧠 Step 1: Thinking
		print_action(philo, "is thinking");

void	*philo_routine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
   	if (philo->table->num_philo == 1)
          return (one_philo(philo));
	while (1)
	{


		// 🍴 Step 2: Taking forks safely (even/odd strategy)
		if (philo->id % 2 == 0)
		{
			// Even ID: Take right fork first
			PM_LOCK(philo->table->forks[philo->id % philo->table->num_philo]);
			print_action(philo, "has taken a fork");

			PM_LOCK(philo->table->forks[philo->id - 1]);
			print_action(philo, "has taken a fork");
		}
		else
		{
			// Odd ID: Take left fork first
			PM_LOCK(philo->table->forks[philo->id - 1]);
			print_action(philo, "has taken a fork");
			PM_LOCK(philo->table->forks[philo->id % philo->table->num_philo]);
			print_action(philo, "has taken a fork");
		}
		// 🍝 Step 3: Eating
		print_action(philo, "is eating");
		philo->last_meal_time = get_time_in_ms();
		ft_usleep(philo->table->time_to_eat);

        //meals limit check
    	philo->meals_eaten++;
        if (philo->table->max_meals > 0 && philo->meals_eaten == philo->table->max_meals)
        {
              PM_LOCK(philo->table->fed_lock);
              philo->table->total_fed++;
              PM_UNLOCK(philo->table->fed_lock);
        }
		// 🔓 Step 4: Releasing forks
		PM_UNLOCK(philo->table->forks[philo->id - 1]);
		PM_UNLOCK(philo->table->forks[philo->id % philo->table->num_philo]);

		// 😴 Step 5: Sleeping
		print_action(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep);
	}

	// This point is never reached in the loop
	return (NULL);
}