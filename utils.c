/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:38:05 by aayad             #+#    #+#             */
/*   Updated: 2025/04/23 12:04:10 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    error_msg(char *str)
{
    printf("%s\n", str);
}

long     ft_atoi(const char *str)
{
    int     i;
    int     sign;
    long     result;
    
    i = 0;
    sign = 1;
    result = 0;
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = (result * 10) + (str[i] - 48);
        i++;
    }
    return (result * sign);
}

size_t  current_time(void)
{
    struct timeval      time;
    
    if (gettimeofday(&time, NULL) == -1)
        error_msg("gettimeofday() error");
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}