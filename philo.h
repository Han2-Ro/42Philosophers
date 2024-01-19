/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:25:41 by hannes            #+#    #+#             */
/*   Updated: 2024/01/19 14:28:59 by hrother          ###   ########.fr       */
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

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	unsigned int	number_of_times_each_philo_must_eat;
	int				stop;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	meals_mutex;
}				t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				*forks[2];
	t_data			*data;
	unsigned long	last_meal;
	unsigned int	meals_eaten;
}					t_philo;

int				ft_atoi(const char *str);
unsigned long	get_time_ms(void);
void			log_philo(t_philo *philo, char *msg);
void			*philo_routine(void *arg);
void			print_philos(t_philo *philos, const t_data data);
void			monitoring(t_data *data, t_philo *philos);
int				init_all(const int argc, const char **argv, t_data *data, t_philo **philos, int **forks);

#endif
