/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:25:41 by hannes            #+#    #+#             */
/*   Updated: 2024/01/28 19:45:52 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define SUCCESS 0
# define FAILURE 1

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data
{
	int				n_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_think;
	unsigned int	number_of_times_each_philo_must_eat;
	int				stop;
	unsigned long	start_time;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	meals_mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
};

struct s_philo
{
	pthread_t		thread;
	int				id;
	pthread_mutex_t	*forks[2];
	t_data			*data;
	unsigned long	last_meal;
	unsigned int	meals_eaten;
};

int				ft_atoi(const char *str);
unsigned long	get_time_ms(void);
void			log_philo(t_philo *philo, const char *msg);
int				check_stop(t_philo *philo);
void			*philo_routine(void *arg);
void			print_philos(t_data *data);
void			monitoring(t_data *data);
int				init_all(const int argc, const char **argv, t_data *data);

#endif
