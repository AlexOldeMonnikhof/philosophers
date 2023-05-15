/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:58:48 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/15 17:00:18 by aolde-mo         ###   ########.fr       */
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
	{
		data->time_to_sleep = ms;
		data->no_of_times_each_philosopher_must_eat = 0;
	}
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

void	parse_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo));
	if (!data->philo)
		ft_errno("malloc error");
	data->philo->philo_no = malloc(data->no_of_philosophers * sizeof(int));
	if (!data->philo->philo_no)
		ft_errno("malloc error");
	while (i < data->no_of_philosophers)
	{
		data->philo->philo_no[i] = i + 1;
		i++;
	}
	data->philo->th = malloc(data->no_of_philosophers * sizeof(pthread_t));
	if (!data->philo->th)
		ft_errno("malloc error");
	data->philo->l_fork = malloc(data->no_of_philosophers * sizeof(pthread_mutex_t));
	if (!data->philo->l_fork)
		ft_errno("malloc error");
	data->philo->r_fork = malloc(data->no_of_philosophers * sizeof(pthread_mutex_t));
	if (!data->philo->r_fork)
		ft_errno("malloc error");
}

void	parse_mutex(t_dphilo)
{

}

void	ft_parse(t_data *data, int argc, char **argv)
{
	parse_data(data, argc, argv);
	parse_philo(data);
	parse_threads(data->philo);
}
