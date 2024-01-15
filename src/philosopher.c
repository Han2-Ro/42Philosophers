/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:08:00 by hannes            #+#    #+#             */
/*   Updated: 2024/01/15 19:32:48 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	take_forks(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->forks[0]->mutex);
	pthread_mutex_lock(&philo->forks[1]->mutex);
	if (philo->forks[0] && philo->forks[1])
	{
		philo->forks[0]->available = 0;
		printf("%llu: %i has taken a fork\n", get_time_ms(), philo->id);
		philo->forks[1]->available = 0;
		printf("%llu: %i has taken a fork\n", get_time_ms(), philo->id);
		ret = 1;
	}
	pthread_mutex_unlock(&philo->forks[0]->mutex);
	pthread_mutex_unlock(&philo->forks[1]->mutex);
	return (1);
}

void	eat(t_philo *philo)
{
	printf("%llu: %i is eating\n", get_time_ms(), philo->id);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->forks[0]->mutex);
	philo->forks[0]->available = 1;
	pthread_mutex_unlock(&philo->forks[0]->mutex);
	pthread_mutex_lock(&philo->forks[1]->mutex);
	philo->forks[1]->available = 1;
	pthread_mutex_unlock(&philo->forks[1]->mutex);
}

void	sleeping(t_philo *philo)
{
	printf("%llu: %i is sleeping\n", get_time_ms(), philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	printf("%llu: %i is thinking\n", get_time_ms(), philo->id);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->stop == 0)
	{
		while (take_forks(philo) == 0)
		{
			usleep(500);
		}
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}
