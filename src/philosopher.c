/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:08:00 by hannes            #+#    #+#             */
/*   Updated: 2024/01/26 21:50:52 by hrother          ###   ########.fr       */
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

/*
int	take_forks(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->data->fork_mutex);
	//printf("%llu: %i tries to take forks\n", get_time_ms(), philo->id);
	if (*philo->forks[0] == 0 && *philo->forks[1] == 0 && check_stop(philo) == 0)
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
*/

void	eat(t_philo *philo)
{
	/*while (take_forks(philo) == 0)
	{
		if (check_stop(philo) == 1)
			return ;
		usleep(500);
	}*/
	pthread_mutex_lock(philo->forks[0]);
	log_philo(philo, "has taken a fork");
	printf("forks[0]: %p\n", philo->forks[0]);
	if (philo->forks[0] == philo->forks[1])
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_mutex_unlock(philo->forks[0]);
		return ;
	}
	pthread_mutex_lock(philo->forks[1]);
	log_philo(philo, "has taken a fork");
	printf("forks[1]: %p\n", philo->forks[1]);
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
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
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

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time_ms();
	log_philo(philo, "started");
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
