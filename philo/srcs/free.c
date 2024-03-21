/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermolo <alermolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:25:52 by alermolo          #+#    #+#             */
/*   Updated: 2024/03/18 12:51:05 by alermolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_table(t_table *table)
{
	if (table->print_mtx)
		pthread_mutex_destroy(table->print_mtx);
	if (table->death_mtx)
		pthread_mutex_destroy(table->death_mtx);
	if (table->launch_mtx)
		pthread_mutex_destroy(table->launch_mtx);
	if (table->print_mtx)
		free(table->print_mtx);
	if (table->death_mtx)
		free(table->death_mtx);
	if (table->launch_mtx)
		free(table->launch_mtx);
	if (table->forks)
		free(table->forks);
	if (table)
		free(table);
}

int	free_phils(t_phils **phils, int exit_status, int nb)
{
	int	i;

	free_table(phils[0]->table);
	i = 0;
	while (i < nb)
	{
		if (phils[i]->fork_l_mtx)
		{
			pthread_mutex_destroy(phils[i]->fork_l_mtx);
			free(phils[i]->fork_l_mtx);
		}
		if (phils[i])
			free(phils[i]);
		i++;
	}
	if (phils)
		free(phils);
	return (exit_status);
}
