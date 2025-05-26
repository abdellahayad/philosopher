/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:41:10 by aayad             #+#    #+#             */
/*   Updated: 2025/05/22 10:41:12 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_program *program,
			pthread_mutex_t *forks, pthread_t monitor_thread)
{
	int	i;

	i = 0;
	while (i < program->philos->no_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
		{
			clean_all("Error joining philosopher thread", program, forks);
			return (1);
		}
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		clean_all("Error joining monitor thread", program, forks);
		return (1);
	}
	return (0);
}

int	create_threads(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	while (i < program->philos->no_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
				&routine, &program->philos[i]) != 0)
		{
			clean_all("Error creating philosopher thread", program, forks);
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL,
			&monitor, program->philos) != 0)
	{
		clean_all("Error creating monitor thread", program, forks);
		return (1);
	}
	return (join_threads(program, forks, monitor_thread));
}
