/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:53:13 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/06/07 17:37:58 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*one_philo_cycle(void *param)
{
	t_philo		*philo;
	t_data		*data;

	philo = param;
	data = philo->data;
	while (!false)
	{
		if (one_philo_eat(philo))
		{
			print_msg(philo, get_time(data), "died", true);
			break ;
		}
		if (philo->times_eaten == data->times_philo_must_eat)
			break ;
		one_philo_sleep_and_think(philo);
	}
	return (NULL);
}

int	one_philo_eat(t_philo *philo)
{
	t_data		*data;
	long long	time;

	data = philo->data;
	pthread_mutex_lock(philo->data->forks);
	time = get_time(data);
	if (time - philo->last_time_eaten > philo->data->time_to_die)
	{
		pthread_mutex_unlock(philo->data->forks);
		return (1);
	}
	print_msg(philo, time, "has taken a fork", false);
	print_msg(philo, time, "is eating", false);
	acc_usleep(data, data->time_to_eat);
	pthread_mutex_unlock(philo->data->forks);
	philo->last_time_eaten = time + philo->data->time_to_eat;
	philo->times_eaten++;
	return (0);
}

void	one_philo_sleep_and_think(t_philo *philo)
{
	long long	time;

	time = get_time(philo->data);
	print_msg(philo, time, "is sleeping", false);
	acc_usleep(philo->data, philo->data->time_to_sleep);
	time = get_time(philo->data);
	if (time - philo->last_time_eaten > philo->data->time_to_die)
	{
		print_msg(philo, get_time(philo->data), "died", true);
		return ;
	}
	print_msg(philo, time, "is thinking", false);
}
