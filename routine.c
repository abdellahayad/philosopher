#include "philo.h"

void	eat(t_data *philo)
{
	pthread_mutex_lock(philo->right_fork);
	message("take a fork", YELLOW, philo, philo->id);
	if (philo->no_philos == 1)
	{
		ft_usleep(philo->time_to_die, philo);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	message("take a fork", YELLOW, philo, philo->id);
	philo->eating = 1;
	message("is eating", GREEN, philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meals = current_time();
	philo->meals_count++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat, philo);
	philo->eating = 0;
	
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	slep(t_data *philo)
{
	message("sleeping", BLUE, philo, philo->id);
	ft_usleep(philo->time_to_sleep, philo);
}
void think(t_data *philo)
{
	message("thinking", BLUE, philo, philo->id);
}

void	*routine(void	*ret)
{
	t_data	*philo;

	philo = (t_data *)ret;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo);
	while (!is_die(philo))
	{
		eat(philo);
		slep(philo);
		think(philo);
	}
	return (ret);
}
