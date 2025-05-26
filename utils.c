/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:38:05 by aayad             #+#    #+#             */
/*   Updated: 2025/05/26 13:35:10 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg(char *str)
{
	printf("%s%s\n", RED, str);
}

static int	get_sign(const char *str, int i)
{
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		return (1);
	return (1);
}

long	ft_atoi(char *str)
{
	int		i;
	int		sing;
	long	result;
	long	var;

	i = 0;
	sing = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	sing = get_sign(str, i);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		var = result;
		result = (result * 10) + (str[i++] - '0');
		if (result / 10 != var && sing == 1)
			return (-1);
		else if (result / 10 != var && sing == -1)
			return (0);
	}
	return (result * sing);
}

size_t	current_time(void)
{
	struct timeval	now;
	size_t			ms;

	if (gettimeofday(&now, NULL) == -1)
		error_msg("gettimeofday() error");
	ms = now.tv_sec * (size_t)1000;
	ms += now.tv_usec / 1000;
	return (ms);
}

size_t	ft_usleep(size_t ms, t_data *philo)
{
	size_t	start;
	int		dead;

	start = current_time();
	while ((current_time() - start) < ms)
	{
		usleep(500);
		pthread_mutex_lock(philo->dead_lock);
		dead = *philo->is_dead;
		pthread_mutex_unlock(philo->dead_lock);
		if (dead == 1)
			break ;
	}
	return (0);
}
