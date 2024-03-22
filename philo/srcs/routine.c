/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermolo <alermolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:20:09 by alermolo          #+#    #+#             */
/*   Updated: 2024/03/22 11:31:15 by alermolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_lock(char *str, t_phils *phil)
{
	pthread_mutex_lock(phil->table->death_mtx);
	if (!phil->table->all_alive)
	{
		pthread_mutex_unlock(phil->table->death_mtx);
		return ;
	}
	pthread_mutex_lock(phil->table->print_mtx);
	printf("%06ld %d %s\n", time_diff(phil->start_time), phil->pos + 1, str);
	pthread_mutex_unlock(phil->table->print_mtx);
	pthread_mutex_unlock(phil->table->death_mtx);
}

void	*routine(void *data)
{
	t_phils	*phil;

	phil = (t_phils *)data;
	pthread_mutex_lock(phil->table->launch_mtx);
	pthread_mutex_unlock(phil->table->launch_mtx);
	if (phil->pos % 2 == 0)
	{
		print_lock("is thinking", phil);
		if (phil->table->time_to_eat < phil->table->time_to_die)
			ft_usleep(phil->table->time_to_eat, phil);
		else
			ft_usleep(phil->table->time_to_die, phil);
	}
	while ((phil->table->meal_limit == -1
			|| phil->num_of_meals < phil->table->meal_limit)
		&& !philo_died(phil))
	{
		if (philo_eat(phil) == -1)
			return (NULL);
		philo_sleep(phil);
		print_lock("is thinking", phil);
		if (philo_died(phil))
			break ;
	}
	return (0);
}

void	join_threads(t_phils **phils, int nb_phils)
{
	int	i;

	i = 0;
	while (i < nb_phils)
	{
		pthread_join(phils[i]->thread, NULL);
		i++;
	}
}

int	launch_routine(t_phils **phils, int nb_phils)
{
	int				i;
	struct timeval	start;

	pthread_mutex_lock(phils[0]->table->launch_mtx);
	i = 0;
	if (gettimeofday(&start, NULL))
		return (-1);
	while (i < nb_phils)
	{
		phils[i]->start_time = start;
		if (pthread_create(&phils[i]->thread, NULL, routine, phils[i]))
			return (-1);
		i++;
	}
	pthread_mutex_unlock(phils[0]->table->launch_mtx);
	join_threads(phils, nb_phils);
	pthread_mutex_destroy(phils[0]->table->launch_mtx);
	return (0);
}
