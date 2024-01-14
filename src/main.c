/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:10:18 by hannes            #+#    #+#             */
/*   Updated: 2024/01/14 17:30:14 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_data(t_config *config, int argc, const char *argv[])
{
	config->number_of_philosophers = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	if (config->number_of_philosophers < 0 || config->time_to_die < 0
		|| config->time_to_eat < 0 || config->time_to_sleep < 0)
	{
		printf("Error: All arguments must positive integers.\n");
		return (1);
	}
	if (argc == 6)
	{
		config->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		if (config->number_of_times_each_philosopher_must_eat < 0)
		{
			printf("Error: All arguments must positive integers.\n");
			return (1);
		}
	}
	else
		config->number_of_times_each_philosopher_must_eat = -1;
	return (0);
}

t_philo	*init_philos(const t_config config)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * config.number_of_philosophers);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < config.number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].config = &config;
		if (!pthread_create(&philos[i].thread, NULL, &philo_routine, &philos[i]))
			return (free(philos), NULL);
	}
	return (philos);
}

int	main(int argc, const char *argv[])
{
	t_config	config;

	if (argc != 5 && argc != 6)
	{
		printf(
			"usage: ./philo number_of_philosophers time_to_die time_to_eat \
			time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
			);
		return (1);
	}
	if (init_data(&config, argc, argv) == 1)
		return (1);
	if (init_philos(config) == NULL)
		return (1);
	return (0);
}
