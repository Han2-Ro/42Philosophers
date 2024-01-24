/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:57:38 by hannes            #+#    #+#             */
/*   Updated: 2024/01/24 14:00:00 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

unsigned long	get_time_ms(void)
{
	struct timeval	time;
	unsigned long	time_ms;

	gettimeofday(&time, NULL);
	time_ms = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (time_ms);
}

void	print_philos(t_philo *philos, const t_data data)
{
	int	i;

	i = 0;
	while (i < data.number_of_philosophers)
	{
		printf("Philosopher %i, thread %li, meals_eaten %i\n", philos[i].id, philos[i].thread, philos[i].meals_eaten);
		i++;
	}
}

void	log_philo(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->log_mutex);
	printf("%lu: %i %s\n", get_time_ms(), philo->id, msg);
	pthread_mutex_unlock(&philo->data->log_mutex);
}
