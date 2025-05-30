/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:37:57 by aayad             #+#    #+#             */
/*   Updated: 2025/05/29 14:45:39 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_program_mutexes(t_program *program)
{
	if (pthread_mutex_init(&program->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&program->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&program->write_lock);
		return (2);
	}
	if (pthread_mutex_init(&program->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&program->write_lock);
		pthread_mutex_destroy(&program->meal_lock);
		return (3);
	}
	return (0);
}

static int	initialization(t_data *philos, t_program *program,
		pthread_mutex_t *forks, char **argv)
{
	program->philos = philos;
	program->death_flag = 0;
	if (init_program_mutexes(program))
		return (1);
	init_philos(philos, program, forks, argv);
	if (init_forks(forks, ft_atoi(argv[1])) != 0)
	{
		pthread_mutex_destroy(&program->write_lock);
		pthread_mutex_destroy(&program->meal_lock);
		pthread_mutex_destroy(&program->dead_lock);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_data			philos[PH_MAX];
	pthread_mutex_t	forks[PH_MAX];

	if (argc == 5 || argc == 6)
	{
		if (parse_inpt(argv) == 1)
			return (1);
		if (initialization(philos, &program, forks, argv) != 0)
		{
			error_msg("Initialization failed.");
			return (1);
		}
		create_threads(&program, forks);
		clean_all(NULL, &program, forks);
		return (0);
	}
	else
		error_msg("Input Error!");
	return (1);
}
