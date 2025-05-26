/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:41:58 by aayad             #+#    #+#             */
/*   Updated: 2025/05/26 13:35:31 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_die(char *str, char *color, t_data *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = current_time() - philo->times.start_simul;
	printf("%s%zu %d %s%s\n", color, time, id, str, RESET);
	pthread_mutex_unlock(philo->write_lock);
}

void	clean_all(char *msg, t_program *prog, pthread_mutex_t *forks)
{
	int	i;
	int	total;

	if (msg)
		printf("%sError: %s\n", RED, msg);
	pthread_mutex_destroy(&prog->write_lock);
	pthread_mutex_destroy(&prog->dead_lock);
	pthread_mutex_destroy(&prog->meal_lock);
	total = prog->philos->no_philos;
	i = -1;
	while (++i < total)
		pthread_mutex_destroy(&forks[i]);
}
