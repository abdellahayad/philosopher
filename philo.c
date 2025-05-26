/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:37:57 by aayad             #+#    #+#             */
/*   Updated: 2025/05/26 13:26:57 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	initialization(t_data *philos, t_program *program,
		pthread_mutex_t *forks, char **argv)
{
	program->philos = philos;
	program->death_flag = 0;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	init_philos(philos, program, forks, argv);
	init_forks(forks, ft_atoi(argv[1]));
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
		initialization(philos, &program, forks, argv);
		create_threads(&program, forks);
		clean_all(NULL, &program, forks);
		return (0);
	}
	else
		error_msg("Input Error!");
	return (1);
}
