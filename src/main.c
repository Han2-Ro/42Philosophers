/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:10:18 by hannes            #+#    #+#             */
/*   Updated: 2024/01/27 12:42:03 by hrother          ###   ########.fr       */
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
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_data *data)
{
	int	i;

	data->start_time = get_time_ms();
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].last_meal = data->start_time;
		if (
			pthread_create(&data->philos[i].thread,
				NULL,
				&philo_routine,
				&data->philos[i])
			!= 0)
		{
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

//TODO: fix possible data races (done, but check again later)
//TODO: exit immediately on exit condition (improved, but not perfect)
//TODO: figure out how to properly start the simulation
//TODO: go over argument checks
//TODO: one mutex per fork
//TODO: refactor code to shorter functions
//TODO: norminette
int	main(const int argc, const char *argv[])
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf(
			"usage: ./philo number_of_philosophers time_to_die time_to_eat \
			time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
			);
		return (1);
	}
	init_all(argc, argv, &data);
	start_simulation(&data);
	usleep(5000);
	monitoring(&data);
	print_philos(data.philos, &data);
	join_philos(&data);
	free(data.philos);
	free(data.forks);
	destroy_mutexes(&data);
	return (0);
}
