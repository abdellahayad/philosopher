/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:02:52 by aayad             #+#    #+#             */
/*   Updated: 2025/05/26 11:16:05 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_eating(t_data *philo)
{
	philo->eating = 1;
	message("is eating", GREEN, philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->times.last_meals = current_time();
	philo->meals_count++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->times.time_to_eat, philo);
	philo->eating = 0;
}

void	eat(t_data *philo)
{
	pthread_mutex_lock(philo->right_fork);
	message("has take a fork", YELLOW, philo, philo->id);
	if (philo->no_philos == 1)
	{
		ft_usleep(philo->times.time_to_die, philo);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	message("has take a fork", YELLOW, philo, philo->id);
	start_eating(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void	*arg)
{
	t_data	*philo;

	philo = (t_data *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo);
	while (!is_die(philo))
	{
		eat(philo);
		message("is sleeping", BLUE, philo, philo->id);
		ft_usleep(philo->times.time_to_sleep, philo);
		message("is thinking", BLUE, philo, philo->id);
	}
	return (arg);
}
