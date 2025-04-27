#include "philo.h"

void    clean_all(char *str, t_program *program, pthread_mutex_t *forks)
{
    int     i;
    t_data  *data;

    i = 0;
    printf("%s\n", str);
    pthread_mutex_destroy(&program->write_lock);
    pthread_mutex_destroy(&program->dead_lock);
    pthread_mutex_destroy(&program->meal_lock);

    if (forks)
    {
        while (i < data->no_philos)
        {
            pthread_mutex_destroy(&forks[i]);
            i++;
        }
    }
}