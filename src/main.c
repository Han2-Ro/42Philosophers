/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:10:18 by hannes            #+#    #+#             */
/*   Updated: 2024/01/17 14:05:06 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_data(t_data *data, int argc, const char *argv[])
{
	data->stop = 0;
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->number_of_philosophers < 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
	{
		printf("Error: All arguments must positive integers.\n");
		return (1);
	}
	if (argc == 6)
	{
		data->number_of_times_each_philo_must_eat = ft_atoi(argv[5]);
		if (data->number_of_times_each_philo_must_eat < 0)
		{
			printf("Error: All arguments must positive integers.\n");
			return (1);
		}
	}
	else
		data->number_of_times_each_philo_must_eat = 2147483647;
	return (0);
}

int init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->fork_mutex, NULL))
		return (1);
	return (0);
}

t_philo	*init_philos(t_data data, int *forks)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data.number_of_philosophers);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data.number_of_philosophers - 1)
	{
		philos[i].forks[0] = &forks[i];
		philos[i].forks[1] = &forks[i + 1];
		i++;
	}
	philos[i].forks[0] = &forks[i];
	philos[i].forks[1] = &forks[0];
	i = 0;
	while (i < data.number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].data = &data;
		philos[i].last_meal = get_time_ms();
		philos[i].meals_eaten = 0;
		if (pthread_create(&philos[i].thread, NULL, &philo_routine, &philos[i]))
			return (free(philos), NULL);
		i++;
	}
	return (philos);
}

int	*init_forks(const t_data data)
{
	int	*forks;
	int	i;

	forks = malloc(sizeof(int) * data.number_of_philosophers);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		forks[i] = 0;
		i++;
	}
	return (forks);
}

void	join_philos(t_philo *philos, const t_data data)
{
	int	i;

	i = 0;
	while (i < data.number_of_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL))
			return ;
		i++;
	}
}

int	main(int argc, const char *argv[])
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
	if (init_data(&data, argc, argv) == 1)
		return (1);
	forks = init_forks(data);
	philos = init_philos(data, forks);
	if (philos == NULL)
		return (1);
	monitoring(&data, philos);
	join_philos(philos, data);
	return (0);
}
