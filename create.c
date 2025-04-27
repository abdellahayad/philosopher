#include "philo.h"

int     create_thread(t_program *program, pthread_mutex_t *forks)
{
    pthread_t   id_svr;

    if (pthread_create(&id_svr, NULL, monitor, program->philos) != 0)
        clean_all("Error create", program, forks);
    return (0);
}