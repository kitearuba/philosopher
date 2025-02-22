/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/20 19:39:58 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */
/*                               Includes                                     */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "philo.h"

/* ************************************************************************** */
/*                              Structures                                    */
/* ************************************************************************** */

typedef struct	s_table t_table;

typedef	struct	s_philosophers
{
		int	 		id;
        pthread_t	thread;
        long		last_meal_time;
        int			meals_eten;
        t_table		*table;
}	t_philosophers;

typedef struct	s_table
{
		int				num_philosophers;
		int				time_to_die;
		int				time_to_eat;
		int				time_to_sleep;
        pthread_mutex_t	*forks;
        pthread_mutex_t	print_lock;
        t_philosophers	*philosophers;
}	t_table;




/* ************************************************************************** */
/*                          Parsing & Validation                              */
/* ************************************************************************** */

int			parse_strict_atoi(const char *str, char **args);

/* ************************************************************************** */
/*                          Error Handling                                    */
/* ************************************************************************** */

void		fatal_error(const char *msg);

/* ************************************************************************** */
/*                          Initialization                                    */
/* ************************************************************************** */



/* ************************************************************************** */
/*                          Memory Management                                 */
/* ************************************************************************** */

void		free_2d_array(char **arr);

#endif /* PHILO_H */
