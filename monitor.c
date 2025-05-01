#include "philo.h"

int     is_die(t_data   *philo)
{
    pthread_mutex_lock(philo->dead_lock);
    if (*philo->is_dead == 1)
    {
        pthread_mutex_unlock(philo->dead_lock);
        return (1);
    }
    pthread_mutex_unlock(philo->dead_lock);
    return (0);
}

int		check_all_eat(t_data	*philo)
{
	int		i;
	int		count;
	
	count = 0;
	i = 0;
	if (philo[0].meals_required == -1)
		return (0);
	while (i < philo[0].no_philos)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].meals_count >= philo[0].meals_required)	
			count++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (count == philo[0].no_philos)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->is_dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

void    message(char *str, char *color, t_data *philo, int id)
{
    size_t      time;

    pthread_mutex_lock(philo->write_lock);
    time = current_time() - philo->start_simul;
	if (!is_die(philo))
    	printf("%s%zu %d %s%s\n", color, time, id, str, RESET);
    pthread_mutex_unlock(philo->write_lock);
}

static int     check_philo_is_die(t_data *philo)
{
    int     i;
    
    i = 0;
    while (i < philo[0].no_philos)
    {
        pthread_mutex_lock(philo[i].meal_lock);
        if (current_time() - philo[i].last_meals >= philo[i].time_to_die
            && philo[i].eating == 0)
        {
            message("died", RED, &philo[i], philo[i].id);
            pthread_mutex_lock(philo[0].dead_lock);
            *philo->is_dead = 1;
            pthread_mutex_unlock(philo[0].dead_lock);
            return (1);
        }
        pthread_mutex_unlock(philo[i].meal_lock);
        i++;
    }
    return (0);
}

 void   *monitor(void    *ret)
 {
    t_data      *philo;

    philo = (t_data *)ret;
    while (true)
    {
        if (check_philo_is_die(philo) == 1 || check_all_eat(philo) == 1)
           break ;
    }
	return (ret);
 }