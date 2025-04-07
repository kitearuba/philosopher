/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/07 23:11:51 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

/* ************************************************************************** */
/*                               Includes                                     */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

/* ************************************************************************** */
/*                              Structures                                    */
/* ************************************************************************** */

typedef struct s_table t_table;

typedef struct s_philosophers {
  int id;
  pthread_t thread;
  long last_meal_time;
  int meals_eaten;
  t_table *table;
} t_philosophers;

typedef struct s_table {
  int num_philosophers;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int num_meals;
  pthread_mutex_t *forks;
  pthread_mutex_t print_lock;
  t_philosophers *philosophers;
} t_table;

/* ************************************************************************** */
/*                         Initiation & Validation                            */
/* ************************************************************************** */

int init_simulation(t_table *table, int argc, char **argv);

void *philosopher_routine(void *arg);

long get_time_in_ms(void);

void ft_usleep(int milliseconds);

void print_action(t_philosophers *philo, const char *message);

/* ************************************************************************** */
/*                          Error Handling                                    */
/* ************************************************************************** */

void fatal_error(const char *msg);

/* ************************************************************************** */
/*                          Initialization                                    */
/* ************************************************************************** */

/* ************************************************************************** */
/*                          Memory Management                                 */
/* ************************************************************************** */

void free_2d_array(char **arr);

#endif /* PHILO_H */
