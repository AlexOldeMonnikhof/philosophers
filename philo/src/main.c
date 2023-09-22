/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:44:22 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/09/22 14:28:59 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	if (create_threads(&data))
	{
		printf("error while creating or joining thread(s)\n");
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}
