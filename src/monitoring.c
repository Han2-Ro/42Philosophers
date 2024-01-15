/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:18:39 by hrother           #+#    #+#             */
/*   Updated: 2024/01/15 19:58:43 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	monitoring(t_data *data, t_philo *philos)
{
	int	i;

	while (data->stop == 0)
	{
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
		usleep(500);
	}
}
