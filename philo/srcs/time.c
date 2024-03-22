/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermolo <alermolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:56:51 by alermolo          #+#    #+#             */
/*   Updated: 2024/03/22 11:57:23 by alermolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	time_diff(struct timeval start)
{
	struct timeval	current_time;
	long			diff;

	if (gettimeofday(&current_time, NULL))
	{
		printf("Error: gettimeofday failed\n");
		return (-1);
	}
	diff = (current_time.tv_sec - start.tv_sec) * 1000
		+ (current_time.tv_usec - start.tv_usec) / 1000;
	return (diff);
}

static size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		if (write(2, "gettimeofday() error\n", 22) == -1)
			return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t time, t_phils *phil)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
	{
		if (philo_died(phil))
			return (0);
		usleep(500);
	}
	return (0);
}
