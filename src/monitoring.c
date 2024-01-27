/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:18:39 by hrother           #+#    #+#             */
/*   Updated: 2024/01/27 12:07:10 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_death(t_data *data)
{
	int	i;

	i = 0;
	//printf("locking meals_mutex: %p\n", &data->meals_mutex);
	pthread_mutex_lock(&data->meals_mutex);
	while (i < data->n_philos)
	{
		if (data->philos[i].last_meal + data->time_to_die < get_time_ms())
		{
			pthread_mutex_unlock(&data->meals_mutex);
			log_philo(&data->philos[i], "died");
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&data->meals_mutex);
	return (0);
}

int	check_meals(t_data *data)
{
	int	i;

	i = 0;
	//printf("locking meals_mutex: %p\n", &data->meals_mutex);
	pthread_mutex_lock(&data->meals_mutex);
	while (i < data->n_philos)
	{
		if (data->philos[i].meals_eaten < data->number_of_times_each_philo_must_eat)
		{
			pthread_mutex_unlock(&data->meals_mutex);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&data->meals_mutex);
	log_philo(&data->philos[i], "all meals eaten");
	return (1);
}

void	monitoring(t_data *data)
{
	while (1)
	{
		if (check_death(data))
			break ;
		if (check_meals(data))
			break ;
		usleep(200);
	}
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}
