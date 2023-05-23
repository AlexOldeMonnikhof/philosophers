/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:58:48 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/23 19:36:35 by aolde-mo         ###   ########.fr       */
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
	gettimeofday(&data->tv, NULL);
	data->start_time = data->tv.tv_sec * 1000LL + data->tv.tv_usec / 1000LL;
}

void	parse_philo(t_data *data)
{
	int	i;
	int	no;

	i = 0;
	no = data->no_of_philosophers;
	data->th = malloc(no * sizeof(pthread_t));
	data->philo = malloc(no * sizeof(t_philo));
	if (!data->th || !data->philo)
		exit(EXIT_FAILURE);
	while (i < no)
	{
		data->philo[i].philo_no = i + 1;
		data->philo[i].is_eating = false;
		data->philo[i].fork = malloc(sizeof(pthread_mutex_t));
		data->philo[i].data = data;
		if (!data->philo[i].fork \
			|| pthread_mutex_init(data->philo[i].fork, NULL))
			exit(EXIT_FAILURE);
		i++;
	}
}

void	parse_mutex(t_data *data)
{
	int		i;
	int		no;

	i = 0;
	no = data->no_of_philosophers;
	while (i < no)
	{
		data->philo[i].l_fork = data->philo[i].fork;
		data->philo[i].r_fork = data->philo[(i + 1) % no].fork;
		i++;
	}
}

void	ft_parse(t_data *data, int argc, char **argv)
{
	parse_data(data, argc, argv);
	parse_philo(data);
	parse_mutex(data);
}
