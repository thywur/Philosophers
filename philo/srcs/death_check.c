/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermolo <alermolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:08:49 by alermolo          #+#    #+#             */
/*   Updated: 2024/03/12 14:08:58 by alermolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_death(t_phils *phil)
{
	pthread_mutex_lock(phil->table->death_mtx);
	if (!phil->table->all_alive)
	{
		pthread_mutex_unlock(phil->table->death_mtx);
		return ;
	}
	phil->table->all_alive = 0;
	pthread_mutex_lock(phil->table->print_mtx);
	printf("%06ld %d died\n", time_diff(phil->start_time), phil->pos + 1);
	pthread_mutex_unlock(phil->table->print_mtx);
	pthread_mutex_unlock(phil->table->death_mtx);
}

int	philo_died(t_phils *phil)
{
	if (time_diff(phil->start_time) - phil->prev_meal
		> phil->table->time_to_die)
	{
		print_death(phil);
		return (1);
	}
	pthread_mutex_lock(phil->table->death_mtx);
	if (!phil->table->all_alive)
	{
		pthread_mutex_unlock(phil->table->death_mtx);
		return (1);
	}
	pthread_mutex_unlock(phil->table->death_mtx);
	return (0);
}
