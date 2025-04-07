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

static int	parse_args(t_table *table, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Error: Wrong number of arguments\n"), 1);
	table->num_philosophers = atoi(argv[1]);
	table->time_to_die = atoi(argv[2]);
	table->time_to_eat = atoi(argv[3]);
	table->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		table->num_meals = atoi(argv[5]);
	else
		table->num_meals = -1;
	if (table->num_philosophers < 1 || table->time_to_die < 1
			|| table->time_to_eat < 1 || table->time_to_sleep < 1
			|| (argc == 6 && table->num_meals < 1))
		return (printf("Error: Invalid arguments values\n"), 1);
	return (0);
}

int	init_simulation(t_table *table, int argc, char **argv)
{
	int	i;

	i = 0;
	if (parse_args (table, argc, argv))
		return (1);
	table->philosophers = malloc
		(sizeof(t_philosophers) * table->num_philosophers);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philosophers);
	pthread_mutex_init(&table->print_lock, NULL);
	while (i < table->num_philosophers)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	return (0);
}
