/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/06/24 10:22:13 by chrrodri         ###   ########.fr       */
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
/*                           Constants and Colors                             */
/* ************************************************************************** */

# define RESET			"\033[0m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define CYAN			"\033[36m"
# define PHILO_COLOR_CAP	0
# define PHILO_PRINT_CAP	0

/* ************************************************************************** */
/*                                   ENUM                                     */
/* ************************************************************************** */

typedef enum e_state
{
	STATE_EATING,
	STATE_SLEEPING,
	STATE_THINKING,
	STATE_TAKEN_FORK,
	STATE_DIED
}	t_state;

typedef enum e_status
{
	SUCCESS = 0,
	FAILURE = 1
}	t_status;

/* ************************************************************************** */
/*                                Structures                                  */
/* ************************************************************************** */

typedef struct s_table	t_table;

typedef struct s_philosophers
{
	int				id;
	int				meals_eaten;
	int				is_fed;
	long			last_meal_time;
	pthread_t		thread;
	t_table			*table;
}	t_philosophers;

typedef struct s_table
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				total_fed;
	int				someone_died;
	int				simulation_ended;
	int				log_colored;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_print_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	fed_lock;
	pthread_mutex_t	simulation_lock;
	t_philosophers	*philosophers;
}	t_table;

/* ************************************************************************** */
/*                                 Functions                                  */
/* ************************************************************************** */

void		*philo_routine(void *arg);
void		unlock_forks(t_philosophers *philo);
void		lock_fork(t_philosophers *philo, int fork_index);
long		get_time_in_ms(void);
void		ft_usleep(int milliseconds, t_table *table);
void		print_action(t_philosophers *philo, t_state state);
void		print_meal_summary(t_table *table);
void		*monitor_death(void *arg);
void		cleanup_simulation(t_table *table);
int			is_simulation_ended(t_table *table);
void		set_simulation_end(t_table *table);
t_status	init_simulation(t_table *table, int argc, char **argv);
int			safe_atoi(const char *str);

#endif //PHILO_H
