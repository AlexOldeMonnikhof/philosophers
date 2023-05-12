/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:58:48 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/12 17:36:14 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_correct_arguments(t_data *data, int ms, int i)
{
	if (i == 1)
		data->no_of_philosophers = ms;
	else if (i == 2)
		data->time_to_die = ms;
	else if (i == 3)
		data->time_to_eat = ms;
	else if (i == 4)
		data->time_to_sleep = ms;
	else
		data->no_of_times_each_philosopher_must_eat = ms;
}

void	parse_data(t_data *data, int argc, char **argv)
{
	int	i;
	int	ms;

	i = 1;
	while (argv[i])
	{
		ms = ft_atoi_data(argv[i]);
		if (!ms)
			ft_error("invalid argument(s)...");
		parse_correct_arguments(data, ms, i);
		i++;
	}
}

void	parse_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->no_of_philosophers)
		philo->philo_no = i++ + 1;
	philo->th = malloc(data->no_of_philosophers * sizeof(pthread_t));
	if (!philo->th)
		ft_errno("malloc error");
	philo->l_fork = malloc(data->no_of_philosophers * sizeof(pthread_mutex_t));
	if (!philo->l_fork)
		ft_errno("malloc error");
	philo->r_fork = malloc(data->no_of_philosophers * sizeof(pthread_mutex_t));
	if (!philo->r_fork)
		ft_errno("malloc error");
}


void	ft_parse(t_data *data, int argc, char **argv)
{
	parse_data(data, argc, argv);
	parse_philo(data, data->philo);
}
