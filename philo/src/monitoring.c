/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:31:51 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/06/06 18:05:40 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	monitoring(t_data *data)
{
	int		i;
	int		have_eaten_enough;

	have_eaten_enough = 0;
	while (check_if_died(data) == false && check_if_all_ate(data) == false)
	{
		i = 0;
		while (i < data->no_of_philosophers)
		{
			pthread_mutex_lock(&data->check_eat_count);
			if (data->philo[i].times_eaten == data->times_philo_must_eat)
				have_eaten_enough++;
			if (have_eaten_enough == data->no_of_philosophers)
			{
				pthread_mutex_lock(&data->all_ate_mutex);
				data->all_ate = true;
				pthread_mutex_unlock(&data->all_ate_mutex);
				pthread_mutex_unlock(&data->check_eat_count);
				break ;
			}
			pthread_mutex_unlock(&data->check_eat_count);
			i++;
		}
	}
}

bool	check_if_died(t_data *data)
{
	pthread_mutex_lock(&data->die_mutex);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->die_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->die_mutex);
	return (false);
}

bool	check_if_all_ate(t_data *data)
{
	pthread_mutex_lock(&data->all_ate_mutex);
	if (data->all_ate)
	{
		pthread_mutex_unlock(&data->all_ate_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->all_ate_mutex);
	return (false);
}
