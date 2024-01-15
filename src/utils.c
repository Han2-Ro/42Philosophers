/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:57:38 by hannes            #+#    #+#             */
/*   Updated: 2024/01/15 13:20:00 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

void	print_philos(t_philo *philos, const t_config config)
{
	int	i;

	i = 0;
	while (i < config.number_of_philosophers)
	{
		printf("Philosopher %i, thread %li\n", philos[i].id, philos[i].thread);
		i++;
	}
}
