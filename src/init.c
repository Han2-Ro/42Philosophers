/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:15:36 by hrother           #+#    #+#             */
/*   Updated: 2024/01/27 12:18:36 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_data(t_data *data, const int argc, const char *argv[])
{
	data->stop = 0;
	data->n_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->n_philos < 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
	{
		printf("Error: All arguments must positive integers.\n");
		return (1);
	}
	if (argc == 6)
	{
		data->number_of_times_each_philo_must_eat = ft_atoi(argv[5]);
		if (data->number_of_times_each_philo_must_eat < 1)
		{
			printf("Error: All arguments must positive integers.\n");
			return (1);
		}
	}
	else
		data->number_of_times_each_philo_must_eat = 2147483647;
	return (0);
}

int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->log_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->stop_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->meals_mutex, NULL))
		return (1);
	return (0);
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->n_philos)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].meals_eaten = 0;
		i++;
	}
	return (philos);
}

int	asign_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (i % 2 == 0)
		{
			data->philos[i].forks[0] = &data->forks[i];
			data->philos[i].forks[1] = &data->forks[(i + 1) % data->n_philos];
		}
		else
		{
			data->philos[i].forks[0] = &data->forks[(i + 1) % data->n_philos];
			data->philos[i].forks[1] = &data->forks[i];
		}
		i++;
	}
	return (SUCCESS);
}

pthread_mutex_t	*init_forks(const t_data data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * data.n_philos);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data.n_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (free(forks), NULL);
		i++;
	}
	return (forks);
}

int	init_all(const int argc, const char **argv, t_data *data)
{
	if (init_data(data, argc, argv) == 1)
		return (FAILURE);
	init_mutexes(data);
	data->forks = init_forks(*data);
	if (data->forks == NULL)
		return (FAILURE);
	data->philos = init_philos(data);
	if (data->philos == NULL)
		return (free(data->forks), FAILURE);
	asign_forks(data);
    return (SUCCESS);
}
