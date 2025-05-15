#include "philo.h"

int     create_thread(t_program *program, pthread_mutex_t *forks)
{
    pthread_t   id_svr;
	int			i;

    if (pthread_create(&id_svr, NULL, &monitor, program->philos) != 0)
        clean_all("Error create", program, forks);
	i = 0;
	while (i < program->philos[0].no_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &routine,
			&program->philos[i]) != 0)
			clean_all("Erroe create", program, forks);
		i++;
	}
	if (pthread_detach(id_svr) != 0)
			clean_all("Erroe create", program, forks);
	i = 0;
	while (i < program->philos[0].no_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			clean_all("Erroe create", program, forks);
		i++; 
	}
    return (0);
}