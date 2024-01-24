/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:10:18 by hannes            #+#    #+#             */
/*   Updated: 2024/01/24 14:22:49 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->fork_mutex);
	pthread_mutex_destroy(&data->log_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->meals_mutex);
}

void	join_philos(t_philo *philos, const t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

//TODO: fix possible data races (done, but check again later)
//TODO: exit immediately on exit condition (improved, but not perfect)
//TODO: one mutex per fork
//TODO: refactor code to shorter functions
//TODO: norminette
int	main(const int argc, const char *argv[])
{
	t_data	data;
	t_philo	*philos;
	int		*forks;

	if (argc != 5 && argc != 6)
	{
		printf(
			"usage: ./philo number_of_philosophers time_to_die time_to_eat \
			time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
			);
		return (1);
	}
	philos = NULL;
	init_all(argc, argv, &data, &philos, &forks);
	monitoring(&data, philos);
	print_philos(philos, &data);
	join_philos(philos, &data);
	free(philos);
	free(forks);
	destroy_mutexes(&data);
	return (0);
}
