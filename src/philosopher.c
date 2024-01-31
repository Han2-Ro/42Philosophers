/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:08:00 by hannes            #+#    #+#             */
/*   Updated: 2024/01/31 20:37:52 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philo *philo) // TODO: protect mutex_locks
{
	pthread_mutex_lock(philo->forks[0]);
	log_philo(philo, "has taken a fork", false);
	if (philo->forks[0] == philo->forks[1])
	{
		usleep(philo->data->time_die * 1000 + 1000);
		return ;
	}
	pthread_mutex_lock(philo->forks[1]);
	log_philo(philo, "has taken a fork", false);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	if (check_stop(philo) == 1)
	{
		pthread_mutex_unlock(philo->forks[0]);
		pthread_mutex_unlock(philo->forks[1]);
		return ;
	}
	log_philo(philo, "is eating", false);
	pthread_mutex_lock(&philo->data->meals_mutex);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->data->meals_mutex);
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_lock(&philo->data->meals_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meals_mutex);
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
}

void	sleeping(t_philo *philo)
{
	log_philo(philo, "is sleeping", false);
	usleep(philo->data->time_sleep * 1000);
}

void	think(t_philo *philo)
{
	int	time_to_think;

	log_philo(philo, "is thinking", false);
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
	// log_philo(philo, "started", true);
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
