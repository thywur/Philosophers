/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermolo <alermolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:05:17 by alermolo          #+#    #+#             */
/*   Updated: 2024/03/18 16:23:28 by alermolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	take_fork(t_phils *phil, int *fork, pthread_mutex_t *fork_mtx)
{
	pthread_mutex_lock(fork_mtx);
	if (!*fork)
	{
		*fork = phil->pos + 1;
		print_lock("has taken a fork", phil);
		pthread_mutex_unlock(fork_mtx);
		return (phil->pos + 1);
	}
	pthread_mutex_unlock(fork_mtx);
	return (0);
}

static void	try_forks(t_phils *phil)
{
	int	left;
	int	right;

	left = 0;
	right = 0;
	while (left != phil->pos + 1 || right != phil->pos + 1)
	{
		if (philo_died(phil))
			return ;
		if (left != phil->pos + 1)
			left = take_fork(phil, phil->fork_l, phil->fork_l_mtx);
		if (right != phil->pos + 1)
			right = take_fork(phil, phil->fork_r, phil->fork_r_mtx);
		usleep(phil->table->nb_phils * 10);
	}
}

int	philo_eat(t_phils *phil)
{
	if (philo_died(phil))
		return (0);
	try_forks(phil);
	print_lock("is eating", phil);
	phil->prev_meal = time_diff(phil->start_time);
	if (phil->prev_meal == -1)
		return (-1);
	phil->num_of_meals++;
	ft_usleep(phil->table->time_to_eat, phil);
	pthread_mutex_lock(phil->fork_r_mtx);
	*phil->fork_r = 0;
	pthread_mutex_unlock(phil->fork_r_mtx);
	pthread_mutex_lock(phil->fork_l_mtx);
	*phil->fork_l = 0;
	pthread_mutex_unlock(phil->fork_l_mtx);
	return (0);
}

void	philo_sleep(t_phils *phil)
{
	if (philo_died(phil))
		return ;
	print_lock("is sleeping", phil);
	ft_usleep(phil->table->time_to_sleep, phil);
	return ;
}
