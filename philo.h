/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:25:41 by hannes            #+#    #+#             */
/*   Updated: 2024/01/15 19:56:58 by hrother          ###   ########.fr       */
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
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philo_must_eat;
	int	stop;
}				t_data;

typedef struct s_fork
{
	int				available;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	t_fork			*forks[2];
	t_data			*data;
	unsigned long long		last_meal;
	unsigned int	meals_eaten;
}					t_philo;

int				ft_atoi(const char *str);
unsigned long long	get_time_ms(void);
void			*philo_routine(void *arg);
void			print_philos(t_philo *philos, const t_data data);
void			monitoring(t_data *data, t_philo *philos);

#endif
