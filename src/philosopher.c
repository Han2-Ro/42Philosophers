/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:08:00 by hannes            #+#    #+#             */
/*   Updated: 2024/01/14 22:09:48 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat(t_philo *philo)
{
	printf("<timestamp> %i is eating\n", philo->id);
	usleep(philo->config->time_to_eat);
}

void	sleeping(t_philo *philo)
{
	printf("<timestamp> %i is eating\n", philo->id);
	usleep(philo->config->time_to_eat);
}

void	think(t_philo *philo)
{
	printf("<timestamp> %i is eating\n", philo->id);
	usleep(philo->config->time_to_eat);
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
