/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:18:39 by hrother           #+#    #+#             */
/*   Updated: 2024/01/17 14:09:56 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	check_death(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (philos[i].last_meal + data->time_to_die < get_time_ms())
		{
			printf("%llu: %i died\n", get_time_ms(), philos[i].id);
			data->stop = 1;
			return ;
		}
		i++;
	}
}

void	check_meals(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (philos[i].meals_eaten < data->number_of_times_each_philo_must_eat)
			return ;
		i++;
	}
	data->stop = 1;
}

void	monitoring(t_data *data, t_philo *philos)
{
	while (data->stop == 0)
	{
		check_death(data, philos);
		check_meals(data, philos);
		usleep(500);
	}
}
