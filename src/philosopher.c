/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:08:00 by hannes            #+#    #+#             */
/*   Updated: 2024/01/28 20:50:53 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_stop(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->data->stop_mutex);
	ret = philo->data->stop;
	//printf("%i stop: %i\n", philo->id, ret);
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (ret);
}

void	take_forks(t_philo *philo) //TODO: protect mutex_locks
{
	pthread_mutex_lock(philo->forks[0]);
	log_philo(philo, "has taken a fork");
	if (philo->forks[0] == philo->forks[1])
	{
		usleep(philo->data->time_die * 1000 + 1000);
		return ;
	}
	pthread_mutex_lock(philo->forks[1]);
	log_philo(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	if (check_stop(philo) == 1)
	{
		pthread_mutex_unlock(philo->forks[0]);
		pthread_mutex_unlock(philo->forks[1]);
		return ;
	}
	log_philo(philo, "is eating");
	pthread_mutex_lock(&philo->data->meals_mutex);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++; //TODO: consider moving this after the sleep
	pthread_mutex_unlock(&philo->data->meals_mutex);
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
}

void	sleeping(t_philo *philo)
{
	log_philo(philo, "is sleeping");
	usleep(philo->data->time_sleep * 1000);
}

void	think(t_philo *philo)
{
	int	time_to_think;

	log_philo(philo, "is thinking");
	if (philo->data->n_philos % 2 == 0)
	{
		time_to_think = philo->data->time_eat * 0.5 - philo->data->time_sleep;
	}
	else
	{
		time_to_think = philo->data->time_eat * 1.5 - philo->data->time_sleep;
	}
	if (time_to_think > 0)
		usleep(time_to_think * 1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->data->time_eat * 1000 / 2);
	//log_philo(philo, "started");
	while (1)
	{
		eat(philo);
		if (check_stop(philo) == 1)
			break ;
		sleeping(philo);
		if (check_stop(philo) == 1)
			break ;
		think(philo);
	}
	return (NULL);
}
