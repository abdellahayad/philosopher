#include "philo.h"

void    clean_all(char *str, t_program *program, pthread_mutex_t *forks)
{
    int     i;

    i = 0;
	if (str)
    	printf("%s%s\n", RED, str);
    pthread_mutex_destroy(&program->write_lock);
    pthread_mutex_destroy(&program->dead_lock);
    pthread_mutex_destroy(&program->meal_lock);
 	while (i < program->philos[0].no_philos)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
}