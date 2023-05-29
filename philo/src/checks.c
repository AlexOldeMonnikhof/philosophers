/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:06:31 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/29 18:53:28 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	arg_check(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (!argv[1][0] || !argv[2][0] || !argv[3][0] || !argv[4][0])
		return (1);
	if (argc == 6)
	{
		if (!argv[5][0])
			return (1);
	}
	return (0);
}