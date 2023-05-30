/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:44:22 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/30 14:49:20 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// void	ft_leaks()
// {
// 	system("leaks -s philo");
// }

int	main(int argc, char **argv)
{
	t_data	data;

	if (arg_check(argc, argv))
	{
		printf("empty or invalid number of argument(s)\n");
		return (1);
	}
	if (parse_all(&data, argv))
	{
		printf("invalid argument(s) or malloc error\n");
		return (1);
	}
	if (create_and_join_threads(&data))
	{
		printf("error while creating or joining thread(s)\n");
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}

// atexit(ft_leaks);