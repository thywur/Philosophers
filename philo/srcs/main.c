/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alermolo <alermolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:57:14 by alermolo          #+#    #+#             */
/*   Updated: 2024/03/18 14:32:27 by alermolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	args_ok(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!str_is_num(argv[i]))
		{
			printf("Error: argument is not a valid number\n");
			return (0);
		}
		if (ft_atol(argv[i]) <= 0 || ft_atol(argv[i]) > INT_MAX)
		{
			printf("Error: argument is not a valid number\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_phils	**phils;

	if (!args_ok(argc, argv))
		return (-1);
	phils = malloc(sizeof(t_phils) * ft_atoi(argv[1]));
	if (!phils)
		return (-1);
	if (init_phils(phils, argc, argv) == -1)
		return (free_phils(phils, -1, ft_atoi(argv[1])));
	if (launch_routine(phils, ft_atoi(argv[1])) == -1)
		return (free_phils(phils, -1, ft_atoi(argv[1])));
	return (free_phils(phils, 0, ft_atoi(argv[1])));
}
