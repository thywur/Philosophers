/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermolo <alermolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:11:02 by alermolo          #+#    #+#             */
/*   Updated: 2024/03/13 13:20:17 by alermolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutexes(t_table *table)
{
	pthread_mutex_t	*print_mtx;
	pthread_mutex_t	*death_mtx;
	pthread_mutex_t	*launch_mtx;

	print_mtx = malloc(sizeof(pthread_mutex_t));
	if (!print_mtx)
		return (-1);
	death_mtx = malloc(sizeof(pthread_mutex_t));
	if (!death_mtx)
		return (-1);
	launch_mtx = malloc(sizeof(pthread_mutex_t));
	if (!launch_mtx)
		return (-1);
	if (pthread_mutex_init(print_mtx, NULL) != 0
		|| pthread_mutex_init(death_mtx, NULL) != 0
		|| pthread_mutex_init(launch_mtx, NULL) != 0)
		return (-1);
	table->print_mtx = print_mtx;
	table->death_mtx = death_mtx;
	table->launch_mtx = launch_mtx;
	return (0);
}

int	init_table(t_table *table, int argc, char **argv)
{
	table->all_alive = 1;
	table->nb_phils = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->meal_limit = -1;
	if (argc == 6)
		table->meal_limit = ft_atoi(argv[5]);
	table->forks = malloc(sizeof(int) * table->nb_phils);
	if (!table->forks)
		return (-1);
	memset(table->forks, 0, sizeof(int) * table->nb_phils);
	if (init_mutexes(table) == -1)
		return (-1);
	return (0);
}

int	init_forks(t_table *table, t_phils **phils, int i)
{
	pthread_mutex_t	*fork_l_mtx;

	fork_l_mtx = malloc(sizeof(pthread_mutex_t));
	if (!fork_l_mtx)
		return (-1);
	if (pthread_mutex_init(fork_l_mtx, NULL) != 0)
		return (-1);
	phils[i]->fork_l_mtx = fork_l_mtx;
	if (i > 0)
		phils[i]->fork_r_mtx = phils[i - 1]->fork_l_mtx;
	phils[i]->fork_l = &table->forks[i];
	if (i > 0)
		phils[i]->fork_r = &table->forks[i - 1];
	else
		phils[i]->fork_r = &table->forks[table->nb_phils - 1];
	return (0);
}

int	init_phils(t_phils **phils, int argc, char **argv)
{
	int		i;
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (-1);
	if (init_table(table, argc, argv) == -1)
		return (-1);
	i = 0;
	while (i < table->nb_phils)
	{
		phils[i] = malloc(sizeof(t_phils));
		if (!phils[i])
			return (-1);
		phils[i]->table = table;
		phils[i]->pos = i;
		phils[i]->prev_meal = 0;
		phils[i]->num_of_meals = 0;
		if (init_forks(table, phils, i) == -1)
			return (-1);
		i++;
	}
	phils[0]->fork_r_mtx = phils[table->nb_phils - 1]->fork_l_mtx;
	return (0);
}
