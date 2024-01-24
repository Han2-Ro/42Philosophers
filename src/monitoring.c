/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:18:39 by hrother           #+#    #+#             */
/*   Updated: 2024/01/24 14:13:50 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_death(t_data *data, t_philo *philos)
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
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&data->meals_mutex);
	return (0);
}

int	check_meals(t_data *data, t_philo *philos)
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
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&data->meals_mutex);
	return (1);
}

void	monitoring(t_data *data, t_philo *philos)
{
	while (1)
	{
		if (check_death(data, philos))
			break ;
		if (check_meals(data, philos))
			break ;
		usleep(200);
	}
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}
