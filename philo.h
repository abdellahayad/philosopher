/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayad <aayad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:37:47 by aayad             #+#    #+#             */
/*   Updated: 2025/04/27 21:28:44 by aayad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define PH_MAX 200

typedef struct s_data
{
    pthread_t   thread;
    size_t      last_meals;
    size_t      start_simul;
    size_t      time_to_eat;
    size_t      time_to_die;
    size_t      time_to_sleep;
    int         id;
    int         eating;
    int         no_philos;
    int         meals_count;
    int         meals_required;
    int         *is_dead;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*write_lock;
    
}           t_data;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

typedef struct s_program
{
    pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_data			*philos;
    int             death_flag;
}   t_program;

void    error_msg(char *str);
int     parse_inpt(char **argv);
long    ft_atoi(const char *str);
void    init_data(t_data *data, t_program *program);
void    init_forks(pthread_mutex_t *forks, int philo_no);
void    init_philos(t_data *philos, t_program *program,
        pthread_mutex_t *forks, char **argv);
size_t  current_time(void);
int     create_thread(t_program *program, pthread_mutex_t *forks);
void    clean_all(char *str, t_program *program, pthread_mutex_t *forks);
void   *monitor(void *ret);
void    message(char *str, char *color, t_data *philo, int id);

#endif