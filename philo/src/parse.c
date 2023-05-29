/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:58:48 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/29 19:37:20 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

int	parse_data(t_data *data, char **argv)
{
	int	i;
	int	ms;

	i = 1;
	while (argv[i])
	{
		ms = ft_atoi_data(argv[i]);
		if (ms <= 0)
		{
			printf("arguments must be > 0 and < int_max\n");
			return (1);
		}
		parse_correct_arguments(data, ms, i);
		i++;
	}
	data->status = malloc(sizeof(t_status));
	if (!data->status)
	{
		printf("malloc error");
		return (1);
	}
	data->status->has_eaten_enough = 0;
	data->status->all_ate = false;
	data->status->someone_died = false;
	return (0);
}

int	parse_philo(t_data *data)
{
	int		i;
	int		no;

	i = 0;
	no = data->no_of_philosophers;
	data->th = malloc(no * sizeof(pthread_t));
	data->philo = malloc(no * sizeof(t_philo));
	if (pthread_mutex_init(&data->writing, NULL) || !data->th || !data->philo)
		return (1);
	while (i < no)
	{
		data->philo[i].philo_no = i + 1;
		data->philo[i].last_time_eaten = 0;
		data->philo[i].times_eaten = 0;
		data->philo[i].is_eating = false;
		data->philo[i].data = data;
		data->philo[i].fork = malloc(sizeof(pthread_mutex_t));
		if (!data->philo[i].fork \
			|| pthread_mutex_init(data->philo[i].fork, NULL))
			return (2 + i);
		i++;
	}
	return (0);
}

void	connect_forks(t_data *data)
{
	int		i;
	int		no;

	i = 0;
	no = data->no_of_philosophers;
	if (no == 1)
		return ;
	while (i < no)
	{
		data->philo[i].l_fork = data->philo[i].fork;
		data->philo[i].r_fork = data->philo[(i + 1) % no].fork;
		i++;
	}
}

int	parse_all(t_data *data, char **argv)
{
	int	error;

	if (parse_data(data, argv))
		return (1);
	error = parse_philo(data);
	if (error)
		return (free_specific(data, error));
	connect_forks(data);
	return (0);
}
