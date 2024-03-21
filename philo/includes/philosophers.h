/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermolo <alermolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:53:30 by alermolo          #+#    #+#             */
/*   Updated: 2024/03/18 16:21:54 by alermolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>

typedef struct s_table
{
	int				nb_phils;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meal_limit;
	int				*forks;
	int				all_alive;
	pthread_mutex_t	*print_mtx;
	pthread_mutex_t	*death_mtx;
	pthread_mutex_t	*launch_mtx;
}				t_table;

typedef struct s_phils
{
	t_table			*table;
	int				pos;
	long			prev_meal;
	int				num_of_meals;
	int				*fork_r;
	int				*fork_l;
	pthread_mutex_t	*fork_r_mtx;
	pthread_mutex_t	*fork_l_mtx;
	pthread_t		thread;
	struct timeval	start_time;
}				t_phils;

int		ft_atoi(const char *nptr);
long	ft_atol(const char *s);
int		str_is_num(char *s);
int		init_phils(t_phils **phils, int argc, char **argv);
int		free_phils(t_phils **phils, int exit_status, int nb);
int		launch_routine(t_phils **phils, int nb_phils);
void	print_lock(char *str, t_phils *phil);
int		philo_died(t_phils *phil);
int		philo_eat(t_phils *phil);
void	philo_sleep(t_phils *phil);
void	print_death(t_phils *phil);
int		philo_died(t_phils *phil);
long	time_diff(struct timeval start);
int		ft_usleep(size_t time, t_phils *phil);

#endif
