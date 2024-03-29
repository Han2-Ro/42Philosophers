/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:10:18 by hannes            #+#    #+#             */
/*   Updated: 2024/01/31 21:00:31 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->log_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->meals_mutex);
}

void	join_philos(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_data *data)
{
	unsigned int	i;

	data->start_time = get_time_ms();
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				&data->philos[i]) != 0)
		{
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	main(const int argc, const char *argv[])
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("usage: ./philo number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (init_all(argc, argv, &data) == FAILURE)
		return (1);
	start_simulation(&data);
	usleep(1000);
	monitoring(&data);
	join_philos(&data);
	free(data.philos);
	free(data.forks);
	destroy_mutexes(&data);
	return (0);
}
