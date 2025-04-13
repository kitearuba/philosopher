/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/04/07 23:03:30 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static int	safe_atoi(const char *str, int *error)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	*error = 0;
	if (!str || !str[0])
		return (*error = 1, 0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (!str[i])
		return (*error = 1, 0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (*error = 1, 0);
		i++;
	}
	if (str[i] != '\0')
		return (*error = 1, 0);
	return ((int)result);
}

static int	parse_args(t_table *table, int argc, char **argv)
{
	int	error;

	if (argc < 5 || argc > 6)
		return (printf("Error: wrong number of args\n"), 1);
	table->num_philo = safe_atoi(argv[1], &error);
	table->time_to_die = safe_atoi(argv[2], &error);
	table->time_to_eat = safe_atoi(argv[3], &error);
	table->time_to_sleep = safe_atoi(argv[4], &error);
	if (argc == 6)
		table->num_meals = safe_atoi(argv[5], &error);
	else
		table->num_meals = -1;
	if (error || table->num_philo < 1 || table->time_to_die < 1
		|| table->time_to_eat < 1 || table->time_to_sleep < 1
		|| (argc == 6 && table->num_meals < 1))
    {
          printf("Error: wrong number of args\n");
          return (1);
    }
	return (0);
}


int	init_simulation(t_table *table, int argc, char **argv)
{
	int	i;

	i = 0;
	if (parse_args (table, argc, argv))
    {
          free(table);
          return (1);
    }
	table->philosophers = malloc
		(sizeof(t_philosophers) * table->num_philo);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philo);
	pthread_mutex_init(&table->print_lock, NULL);
    pthread_mutex_init(&table->death_lock, NULL);
	pthread_mutex_init(&table->fed_lock, NULL);
	table->someone_died = 0;
	table->total_fed = 0;
    table->simulation_ended = 0;
    if (pthread_mutex_init(&table->simulation_lock, NULL) != 0)
    {
    	printf("Error: simulation_lock init failed\n");
    	return (1);
    }
	while (i < table->num_philo)
		pthread_mutex_init(&table->forks[i++], NULL);
	return (0);
}
