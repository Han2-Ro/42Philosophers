/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:08:00 by hannes            #+#    #+#             */
/*   Updated: 2024/01/17 14:42:08 by hrother          ###   ########.fr       */
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
		printf("%llu: %i has taken a fork\n", get_time_ms(), philo->id);
		*philo->forks[1] = 1;
		printf("%llu: %i has taken a fork\n", get_time_ms(), philo->id);
		ret = 1;
	}
	pthread_mutex_unlock(&philo->data->fork_mutex);
	return (ret);
}

void	eat(t_philo *philo)
{
	while (take_forks(philo) == 0)
	{
		usleep(500);
	}
	printf("%llu: %i is eating\n", get_time_ms(), philo->id);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->data->fork_mutex);
	*philo->forks[0] = 0;
	*philo->forks[1] = 0;
	pthread_mutex_unlock(&philo->data->fork_mutex);
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
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}
