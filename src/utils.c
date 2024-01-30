/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:57:38 by hannes            #+#    #+#             */
/*   Updated: 2024/01/30 15:47:46 by hrother          ###   ########.fr       */
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

unsigned long	get_time_us(void)
{
	struct timeval	time;
	unsigned long	time_ms;

	gettimeofday(&time, NULL);
	time_ms = ((time.tv_sec * 1000000) + (time.tv_usec));
	return (time_ms);
}

int	ft_usleep(int us)
{
	unsigned long	start;
	unsigned long	end;

	start = get_time_us();
	end = start + us;
	while (get_time_us() + 10000 < end)
		usleep((end - get_time_us()) / 2);
	while (get_time_us() < end)
		;
	return (0);
}

int	check_stop(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->data->stop_mutex);
	ret = philo->data->stop;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (ret);
}

void	print_philos(t_data *data)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&data->log_mutex);
	while (i < data->n_philos)
	{
		printf("Philosopher %i, meals_eaten %i, last_meal:%li\n",
			data->philos[i].id, data->philos[i].meals_eaten,
			data->philos[i].last_meal);
		i++;
	}
	pthread_mutex_unlock(&data->log_mutex);
}

void	log_philo(t_philo *philo, const char *msg)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&philo->data->log_mutex);
	if (check_stop(philo))
	{
		msg = "<ended>";
		// return ;
	}
	timestamp = get_time_ms() - philo->data->start_time;
	printf("%05lu\t%i %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->data->log_mutex);
}
