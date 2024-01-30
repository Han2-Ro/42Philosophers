/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:20:08 by hrother           #+#    #+#             */
/*   Updated: 2024/01/30 13:08:40 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned long	get_time_us(void)
{
	struct timeval	time;
	unsigned long	time_ms;

	gettimeofday(&time, NULL);
	time_ms = ((time.tv_sec * 1000000) + (time.tv_usec));
	return (time_ms);
}

int ft_usleep(int us)
{
    unsigned long start;
    unsigned long end;

    start = get_time_us();
    end = start + us;
    while (get_time_us() + 10000 < end)
        usleep((end - get_time_us()) / 2);
    while (get_time_us() < end)
        ;
    return (0);
}

int main(void)
{
    unsigned long start;
    unsigned long end;
    int i = 0;

    printf("usleep(100 * 1000):\n");
    while (i < 100)
    {
        start = get_time_us();
        usleep(100 * 1000);
        end = get_time_us();
        printf("selpt for %li us\n", end - start);
        i++;
    }
    i = 0;
    printf("\n");
    printf("ft_usleep(100 * 1000):\n");
    while (i < 100)
    {
        start = get_time_us();
        ft_usleep(100 * 1000);
        end = get_time_us();
        printf("selpt for %li us\n", end - start);
        i++;
    }
}
