/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:08:00 by hannes            #+#    #+#             */
/*   Updated: 2024/01/19 13:42:04 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	take_forks(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->data->fork_mutex);
	//printf("%llu: %i tries to take forks\n", get_time_ms(), philo->id);
	if (*philo->forks[0] == 0 && *philo->forks[1] == 0)
	{
		*philo->forks[0] = 1;
		log_philo(philo, "has taken a fork");
		*philo->forks[1] = 1;
		log_philo(philo, "has taken a fork");
		ret = 1;
	}
	pthread_mutex_unlock(&philo->data->fork_mutex);
	return (ret);
}

void	eat(t_philo *philo)
{
	while (take_forks(philo) == 0)
	{
		int ms_since_last_meal = get_time_ms() - philo->last_meal;
		if (ms_since_last_meal != 0)
			usleep(500);
	}
	log_philo(philo, "is eating");
	pthread_mutex_lock(&philo->data->meals_mutex);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++; //TODO: consider moving this after the sleep
	pthread_mutex_unlock(&philo->data->meals_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->data->fork_mutex);
	*philo->forks[0] = 0;
	*philo->forks[1] = 0;
	pthread_mutex_unlock(&philo->data->fork_mutex);
}

void	sleeping(t_philo *philo)
{
	log_philo(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	log_philo(philo, "is thinking");
}

int	check_stop(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->data->stop_mutex);
	ret = philo->data->stop;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (ret);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		eat(philo);
		if (check_stop(philo) == 1)
			return (NULL);
		sleeping(philo);
		if (check_stop(philo) == 1)
			return (NULL);
		think(philo);
	}
	return (NULL);
}
