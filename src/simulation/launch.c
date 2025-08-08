#include "../../include/philo.h"

/**
 * @brief Initializes each philosopher and starts their threads.
 *
 * This function sets the simulation's start time, initializes each
 * philosopher's ID, last meal timestamp, and links to the shared table data.
 * Then, it creates a thread for each philosopher to run their routine
 * concurrently.
 *
 * @param table Pointer to the simulation's table structure.
 */

void	start_simulation(t_table *table)
{
    int			i;

    i = 0;
    table->start_time = get_time_in_ms();
    while (i < table->num_philo)
    {
        table->philosophers[i].last_meal_time = table->start_time;
        pthread_create(&table->philosophers[i].thread,
            NULL,
            philo_routine,
            &table->philosophers[i]);
        i++;
    }
}