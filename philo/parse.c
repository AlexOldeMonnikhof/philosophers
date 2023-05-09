/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:58:48 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/09 15:34:21 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_correct_arguments(t_philo *philo, int ms, int i)
{
	if (i == 1)
		philo->number_of_philosophers = ms;
	else if (i == 2)
		philo->time_to_die = ms;
	else if (i == 3)
		philo->time_to_eat = ms;
	else if (i == 4)
		philo->time_to_sleep = ms;
	else
		philo->number_of_times_each_philosopher_must_eat = ms;
}

void	parse_atoi(t_philo *philo, int argc, char **argv)
{
	int	i;
	int	ms;

	i = 1;
	while (argv[i])
	{
		ms = ft_atoi_philo(argv[i]);
		if (!ms)
			ft_error("invalid argument(s)...");
		parse_correct_arguments(philo, ms, i);
		i++;
	}
}


void	ft_parse(t_philo *philo, int argc, char **argv)
{
	parse_atoi(philo, argc, argv);
}
