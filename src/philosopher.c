/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:08:00 by hannes            #+#    #+#             */
/*   Updated: 2024/01/15 13:41:08 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[0]);
	printf("<timestamp>: %i has taken a fork\n", philo->id);
	pthread_mutex_lock(&philo->forks[1]);
	printf("<timestamp>: %i has taken a fork\n", philo->id);
	printf("<timestamp>: %i is eating\n", philo->id);
	usleep(philo->config->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->forks[0]);
	pthread_mutex_unlock(&philo->forks[1]);
}

void	sleeping(t_philo *philo)
{
	printf("<timestamp>: %i is sleeping\n", philo->id);
	usleep(philo->config->time_to_eat * 1000);
}

void	think(t_philo *philo)
{
	printf("<timestamp>: %i is thinking\n", philo->id);
	usleep(philo->config->time_to_eat * 1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->stop)
	{
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}
