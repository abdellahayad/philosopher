/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:51:29 by aayad             #+#    #+#             */
/*   Updated: 2025/05/29 15:25:53 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_forks(t_data *philo, pthread_mutex_t *forks, int i, int count)
{
	philo->left_fork = &forks[i];
	if (i == 0)
		philo->right_fork = &forks[count - 1];
	else
		philo->right_fork = &forks[i - 1];
}

static void	set_locks(t_data *philo, t_program *program)
{
	philo->write_lock = &program->write_lock;
	philo->dead_lock = &program->dead_lock;
	philo->meal_lock = &program->meal_lock;
	philo->is_dead = &program->death_flag;
}

void	init_config(t_data *philo, char **argv)
{
	philo->no_philos = ft_atoi(argv[1]);
	philo->times.time_to_die = ft_atoi(argv[2]);
	philo->times.time_to_eat = ft_atoi(argv[3]);
	philo->times.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->meals_required = ft_atoi(argv[5]);
	else
		philo->meals_required = -1;
}

void	init_philos(t_data *philo, t_program *program,
		pthread_mutex_t *forks, char **argv)
{
	int		i;
	int		count;
	size_t	start;

	count = ft_atoi(argv[1]);
	start = current_time();
	i = 0;
	while (i < count)
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].meals_count = 0;
		init_config(&philo[i], argv);
		philo[i].times.start_simul = start;
		philo[i].times.last_meals = start;
		set_locks(&philo[i], program);
		set_forks(&philo[i], forks, i, count);
		i++;
	}
}

int	init_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
