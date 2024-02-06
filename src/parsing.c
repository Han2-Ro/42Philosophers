/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 22:16:29 by hrother           #+#    #+#             */
/*   Updated: 2024/01/31 21:39:51 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned int	ft_atoi(const char *str)
{
	unsigned int	i;
	unsigned int	res;
	unsigned int	new_res;

	i = 0;
	res = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		new_res = res * 10 + str[i] - '0';
		if (new_res < res)
			return (0);
		res = new_res;
		i++;
	}
	return (res);
}

int	parse_data(t_data *data, const int argc, const char *argv[])
{
	data->stop = false;
	data->n_philos = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_n_times = ft_atoi(argv[5]);
	else
		data->eat_n_times = UINT_MAX;
	if (data->n_philos < 1 || data->time_die < 1 || data->time_eat < 1
		|| data->time_sleep < 1 || data->eat_n_times < 1)
	{
		printf("Error: All arguments must be integers > 0.\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
