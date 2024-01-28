/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:15:36 by hrother           #+#    #+#             */
/*   Updated: 2024/01/28 21:59:42 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_data(t_data *data, const int argc, const char *argv[])
{
	data->stop = 0;
	data->n_philos = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_n_times = ft_atoi(argv[5]);
	else
		data->eat_n_times = UINT_MAX;
	if (data->n_philos < 1 || data->time_die < 1
		|| data->time_eat < 1 || data->time_sleep < 1
		|| data->eat_n_times < 1)
	{
		printf("Error: All arguments must integers > 0.\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->log_mutex, NULL))
		return (FAILURE);
	if (pthread_mutex_init(&data->stop_mutex, NULL))
		return (FAILURE);
	if (pthread_mutex_init(&data->meals_mutex, NULL))
		return (FAILURE);
	return (SUCCESS);
}

int	init_philos(t_data *data)
{
	unsigned int		i;

	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		return (FAILURE);
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meals_eaten = 0;
		i++;
	}
	return (SUCCESS);
}

int	asign_forks(t_data *data)
{
	unsigned int	i;

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

int	init_forks(t_data *data)
{
	unsigned int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (FAILURE);
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (free(data->forks), FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	init_all(const int argc, const char **argv, t_data *data)
{
	if (init_data(data, argc, argv) == 1)
		return (FAILURE);
	if (init_mutexes(data) == FAILURE)
		return (FAILURE);
	if (init_forks(data) == FAILURE)
		return (FAILURE);
	if (init_philos(data) == FAILURE)
		return (free(data->forks), FAILURE);
	asign_forks(data);
	return (SUCCESS);
}
