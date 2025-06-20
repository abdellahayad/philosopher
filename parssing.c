/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:40:22 by aayad             #+#    #+#             */
/*   Updated: 2025/05/22 15:31:11 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

static int	is_numeric_string(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (1);
	while (str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (1);
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

int	parse_inpt(char **argv)
{
	if (ft_atoi(argv[1]) > PH_MAX || ft_atoi(argv[1]) <= 0
		|| is_numeric_string(argv[1]) == 1 || ft_atoi(argv[1]) > INT_MAX)
		return (error_msg("Error : Invalid philos number"), 1);
	if (ft_atoi(argv[2]) <= 0 || is_numeric_string(argv[2]) == 1
		|| ft_atoi(argv[2]) > INT_MAX)
		return (error_msg("Error : Invalid time to die"), 1);
	if (ft_atoi(argv[3]) <= 0 || is_numeric_string(argv[3]) == 1
		|| ft_atoi(argv[3]) > INT_MAX)
		return (error_msg("Error : Invalid time to eat"), 1);
	if (ft_atoi(argv[4]) <= 0 || is_numeric_string(argv[4]) == 1
		|| ft_atoi(argv[4]) > INT_MAX)
		return (error_msg("Error : Invalid time to sleep"), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || is_numeric_string(argv[5]) == 1
			|| ft_atoi(argv[5]) > INT_MAX))
		return (error_msg("Error : Invalid meals count"), 1);
	return (0);
}
