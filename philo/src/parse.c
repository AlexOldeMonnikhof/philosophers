/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:58:48 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/06/07 17:32:43 by aolde-mo         ###   ########.fr       */
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
			return (1);
		parse_correct_arguments(data, ms, i);
		i++;
	}
	data->ate_enough = 0;
	pthread_mutex_init(&data->writing, NULL);
	pthread_mutex_init(&data->check_eat_count, NULL);
	pthread_mutex_init(&data->die_mutex, NULL);
	pthread_mutex_init(&data->all_ate_mutex, NULL);
	data->someone_died = false;
	data->all_ate = false;
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
	if (!data->th || !data->philo)
		return (1);
	while (i < no)
	{
		data->philo[i].philo_no = i + 1;
		data->philo[i].last_time_eaten = 0;
		data->philo[i].times_eaten = 0;
		data->philo[i].data = data;
		i++;
	}
	return (0);
}

int	parse_forks(t_data *data)
{
	int	i;
	int	no;

	i = 0;
	no = data->no_of_philosophers;
	data->forks = malloc(sizeof(pthread_mutex_t) * no);
	if (!data->forks)
		return (1);
	if (no == 1)
		return (0);
	while (i < no)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[(i + 1) % no];
		i++;
	}
	return (0);
}

int	parse_all(t_data *data, char **argv)
{
	if (parse_data(data, argv))
		return (1);
	if (parse_philo(data))
	{
		free_specific(data);
		return (1);
	}
	if (parse_forks(data))
		return (1);
	return (0);
}
