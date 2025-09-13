/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/06/24 22:55:00 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */
/*                                Includes                                    */
/* ************************************************************************** */

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

/* ************************************************************************** */
/*                                   ENUMS                                     */
/* ************************************************************************** */

/**
 * @brief Human-readable action identifiers for logging.
 */
typedef enum e_state
{
	STATE_EATING,
	STATE_SLEEPING,
	STATE_THINKING,
	STATE_TAKEN_FORK,
	STATE_DIED
}	t_state;

/**
 * @brief Unified success/failure return type.
 */
typedef enum e_status
{
	SUCCESS = 0,
	FAILURE = 1
}	t_status;

/* ************************************************************************** */
/*                                Structures                                  */
/* ************************************************************************** */

typedef struct s_table	t_table;

/**
 * @brief Per-philosopher state. All fields that may change at runtime
 *        (last_meal_time, meals_eaten, has_*_fork) are protected
 *        by either state_lock or fork acquisition rules.
 */
typedef struct s_philosophers
{
	int				id;
	int				meals_eaten;
	int				is_fed;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	state_lock;
	int				has_left_fork;
	int				has_right_fork;
	t_table			*table;
}	t_philosophers;

/**
 * @brief Global simulation context shared by all threads.
 *        Note the minimal set of mutexes:
 *        - print_lock: serializes stdout
 *        - fed_lock: protects total_fed & is_fed updates
 *        - simulation_lock: protects simulation_ended flag
 */
typedef struct s_table
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				total_fed;
	int				simulation_ended;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	fed_lock;
	pthread_mutex_t	simulation_lock;
	t_philosophers	*philosophers;
}	t_table;

/* ************************************************************************** */
/*                                 Prototypes                                 */
/* ************************************************************************** */

/* threads */
void		*philo_routine(void *arg);
void		*monitor_death(void *arg);

/* forks */
void		lock_fork(t_philosophers *philo, int fork_index);
void		unlock_forks(t_philosophers *philo);

/* time / sleep */
long		get_time_in_ms(void);
void		ft_usleep(int milliseconds, t_table *table);

/* printing */
void		print_action(t_philosophers *philo, t_state state);

/* lifecycle / end */
int			is_simulation_ended(t_table *table);
int			end_simulation_by_death(t_table *t, t_philosophers *who);
int			end_simulation_all_fed(t_table *t);

/* init / teardown */
t_status	init_simulation(t_table *table, int argc, char **argv);
void		start_simulation(t_table *table);
void		cleanup_simulation(t_table *table);
int			exit_simulation(t_table *table, int code);

/* utils */
int			safe_atoi(const char *str);

#endif /* PHILO_H */