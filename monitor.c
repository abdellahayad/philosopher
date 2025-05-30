/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:05:51 by aayad             #+#    #+#             */
/*   Updated: 2025/05/28 11:53:20 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_die(t_data *philo)
{
	int	is_dead;

	pthread_mutex_lock(philo->dead_lock);
	is_dead = *philo->is_dead;
	pthread_mutex_unlock(philo->dead_lock);
	return (is_dead);
}

static int	check_all_eat(t_data *philo)
{
	int	i;

	if (philo->meals_required == -1)
		return (0);
	i = 0;
	while (i < philo->no_philos)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].meals_count < philo->meals_required)
		{
			pthread_mutex_unlock(philo[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	pthread_mutex_lock(philo->dead_lock);
	*philo->is_dead = 1;
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}

void	message(char *str, char *color, t_data *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	if (is_die(philo))
	{
		pthread_mutex_unlock(philo->write_lock);
		return ;
	}
	time = current_time() - philo->times.start_simul;
	printf("%s%zu %d %s%s\n", color, time, id, str, RESET);
	pthread_mutex_unlock(philo->write_lock);
}

static int	check_philo_is_die(t_data *philo)
{
	int		i;
	size_t	now;

	i = 0;
	now = current_time();
	while (i < philo->no_philos)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (now - philo[i].times.last_meals >= philo[i].times.time_to_die
			&& !philo[i].eating)
		{
			pthread_mutex_lock(philo->dead_lock);
			*philo->is_dead = 1;
			pthread_mutex_unlock(philo->dead_lock);
			print_die("died", RED, &philo[i], philo[i].id);
			pthread_mutex_unlock(philo[i].meal_lock);
			return (1);
		}
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	return (0);
}

void	*monitor(void *ret)
{
	t_data	*philo;
	int		run;

	philo = (t_data *)ret;
	run = 1;
	while (run)
	{
		if (check_all_eat(philo))
			run = 0;
		if (check_philo_is_die(philo))
			run = 0;
	}
	return (ret);
}
