/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:06:31 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/15 16:56:41 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		ft_error("invalid number of arguments");
	if (!argv[1][0] || !argv[2][0] || !argv[3][0] || !argv[4][0])
		ft_error("empty argument(s)");
	if (argc == 6)
	{
		if (!argv[5][0])
			ft_error("empty argument(s)");
	}
}