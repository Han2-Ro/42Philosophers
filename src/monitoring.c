/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:18:39 by hrother           #+#    #+#             */
/*   Updated: 2024/01/19 13:18:27 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	check_death(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	//printf("locking meals_mutex: %p\n", &data->meals_mutex);
	pthread_mutex_lock(&data->meals_mutex);
	while (i < data->number_of_philosophers)
	{
		if (philos[i].last_meal + data->time_to_die < get_time_ms())
		{
			log_philo(&philos[i], "died");
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return ;
		}
		i++;
	}
	pthread_mutex_unlock(&data->meals_mutex);
}

void	check_meals(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	//printf("locking meals_mutex: %p\n", &data->meals_mutex);
	pthread_mutex_lock(&data->meals_mutex);
	while (i < data->number_of_philosophers)
	{
		if (philos[i].meals_eaten < data->number_of_times_each_philo_must_eat)
		{
			pthread_mutex_unlock(&data->meals_mutex);
			return ;
		}
		i++;
	}
	pthread_mutex_unlock(&data->meals_mutex);
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

void	monitoring(t_data *data, t_philo *philos)
{
	while (data->stop == 0)
	{
		check_death(data, philos);
		check_meals(data, philos);
		usleep(5000);
	}
}
