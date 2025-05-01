/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:37:57 by aayad             #+#    #+#             */
/*   Updated: 2025/05/01 10:47:08 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_program       program;
    t_data          philos[PH_MAX];
    pthread_mutex_t forks[PH_MAX];
    
    if (argc == 5 || argc == 6)
    {
        if (parse_inpt(argv) == 1)
            return (1);
        init_philos(philos, &program, forks, argv);
        init_data(philos, &program);
        init_forks(forks, ft_atoi(argv[1]));
        create_thread(&program, forks);
		clean_all("finish", &program, forks);
		return (0);
    }
    else
        error_msg("Input Error\n"
        "Please enter: ./philo <no of philos> <time_to_die>"
            " <time_to_eat> <time_to_sleep> <max_meals>");
}
