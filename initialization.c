#include "philo.h"

void  init_config(t_data *philo, char **argv)
{
      philo->no_philos = ft_atoi(argv[1]);
      philo->time_to_die = ft_atoi(argv[2]);
      philo->time_to_eat = ft_atoi(argv[3]);
      philo->time_to_sleep = ft_atoi(argv[4]);
      if (argv[5])
            philo->meals_required = ft_atoi(argv[5]);
      else
            philo->meals_required = -1;
}

void  init_philos(t_data *philo, t_program *program, pthread_mutex_t *forks,
      char **argv)
{
      int   j;
      int count;

      count = ft_atoi(argv[1]);
      j = 0;
      while (j < count)
      {
            philo[j].id = j + 1;
            philo[j].eating = 0;
            philo[j].meals_count = 0;
            init_config(&philo[j], argv);
            philo[j].start_simul  = current_time();
            philo[j].last_meals = current_time();
            philo[j].write_lock = &program->write_lock;
            philo[j].dead_lock = &program->dead_lock;
            philo[j].meal_lock = &program->meal_lock;
            philo[j].is_dead = &program->death_flag;
            philo[j].left_fork = &forks[j];
            if (j == 0)
                  philo[j].right_fork = &forks[count - 1];
            else
                  philo[j].right_fork = &forks[j - 1];
            j++;
      }
}

void  init_forks(pthread_mutex_t *forks, int philo_no)
{
      int   i;

      i = 0;
      while (i < philo_no)
      {

            pthread_mutex_init(&forks[i], NULL);
            i++;
      }
}

void init_data(t_data   *data, t_program *program)
{
      program->death_flag = 0;
      program->philos = data;
      pthread_mutex_init(&program->write_lock, NULL);
      pthread_mutex_init(&program->meal_lock, NULL);
      pthread_mutex_init(&program->dead_lock, NULL);
}