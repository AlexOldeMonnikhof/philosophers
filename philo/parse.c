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

void	parse_correct_arguments(t_data *data, int ms_or_no, int i)
{
	if (i == 1)
		data->no_of_philosophers = ms_or_no;
	else if (i == 2)
		data->time_to_die = ms_or_no;
	else if (i == 3)
		data->time_to_eat = ms_or_no;
	else if (i == 4)
	{
		data->time_to_sleep = ms_or_no;
		data->times_philo_must_eat = 0;
	}
	else
		data->times_philo_must_eat = ms_or_no;
}

void	parse_data(t_data *data, char **argv)
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
	data->status = malloc(sizeof(t_status));
	// PROTECT!!!
	data->status->has_eaten_enough = 0;
	data->status->all_ate = false;
	data->status->someone_died = false;
	gettimeofday(&data->tv, NULL);
	data->start_time = data->tv.tv_sec * 1000LL + data->tv.tv_usec / 1000LL;
}

void	parse_philo(t_data *data)
{
	t_philo	*philo;
	int		i;
	int		no;

	i = 0;
	no = data->no_of_philosophers;
	data->th = malloc(no * sizeof(pthread_t));
	data->philo = malloc(no * sizeof(t_philo));
	philo = data->philo;
	if (!data->th || !philo)
		exit(EXIT_FAILURE);
	while (i < no)
	{
		philo[i].philo_no = i + 1;
		philo[i].last_time_eaten = 0;
		philo[i].times_eaten = 0;
		philo[i].is_eating = false;
		philo[i].data = data;
		philo[i].fork = malloc(sizeof(pthread_mutex_t));
		if (!philo[i].fork \
			|| pthread_mutex_init(philo[i].fork, NULL))
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

void	ft_parse(t_data *data, char **argv)
{
	parse_data(data, argv);
	parse_philo(data);
	parse_mutex(data);
}
