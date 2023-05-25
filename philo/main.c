/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:44:22 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/23 19:39:10 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_leaks()
{
	// system("leaks -s philo");
}

int	main(int argc, char **argv)
{
	t_data		data;
	
	arg_check(argc, argv);
	ft_parse(&data, argv);
	create_and_join_threads(&data);
	cleanup(&data);
	atexit(ft_leaks);
}
