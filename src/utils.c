/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:57:38 by hannes            #+#    #+#             */
/*   Updated: 2024/01/31 20:59:14 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned long	get_time_ms(void)
{
	struct timeval	time;
	unsigned long	time_ms;

	gettimeofday(&time, NULL);
	time_ms = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (time_ms);
}

bool	check_stop(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->data->stop_mutex);
	ret = philo->data->stop;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (ret);
}

void	log_philo(t_philo *philo, const char *msg, bool print_always)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&philo->data->log_mutex);
	if (!print_always && check_stop(philo))
	{
		pthread_mutex_unlock(&philo->data->log_mutex);
		return ;
	}
	timestamp = get_time_ms() - philo->data->start_time;
	printf("%05lu\t%i %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->data->log_mutex);
}
