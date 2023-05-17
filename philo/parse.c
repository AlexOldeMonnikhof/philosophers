/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:58:48 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/17 20:26:27 by aolde-mo         ###   ########.fr       */
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
	int		i;
	t_philo	*philo;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->no_of_philosophers);
	if (!data->philo)
		ft_errno("malloc error");
	philo = data->philo;
	while (i < data->no_of_philosophers)
	{
		philo[i].philo_no = i + 1;
		philo[i].th = malloc(sizeof(pthread_t));
		philo[i].l_fork = malloc(sizeof(pthread_mutex_t));
		philo[i].r_fork = malloc(sizeof(pthread_mutex_t));
		if (!philo[i].th || !philo[i].l_fork || !philo[i].r_fork)
			ft_errno("malloc error");
		i++;
	}
}

void	parse_mutex(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = data->philo;
	while (i < data->no_of_philosophers)
	{
		if (pthread_mutex_init(philo[i].l_fork, NULL)
			|| pthread_mutex_init(philo[i].r_fork, NULL))
			ft_errno("mutex fail");
		printf("%d ",i);
		i++;
	}
}

void	ft_parse(t_data *data, int argc, char **argv)
{
	parse_data(data, argc, argv);
	parse_philo(data);
	parse_mutex(data);
}
