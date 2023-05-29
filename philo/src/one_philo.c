/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:53:13 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/29 18:53:35 by aolde-mo         ###   ########.fr       */
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
		if (data->status->all_ate == true)
			break ;
		if (one_philo_eat(philo))
		{
			print_msg(philo, get_time(data), "died", true);
			break ;
		}
		one_philo_sleep(philo);
	}
	return (NULL);
}

int	one_philo_eat(t_philo *philo)
{
	long long	time;
	t_status	*status;

	status = philo->data->status;
	pthread_mutex_lock(philo->fork);
	time = get_time(philo->data);
	if (time - philo->last_time_eaten > philo->data->time_to_die)
	{
		pthread_mutex_unlock(philo->fork);
		return (1);
	}
	print_msg(philo, time, "has taken a fork", false);
	print_msg(philo, time, "is eating", false);
	acc_usleep(philo->data, philo->data->time_to_eat);
	pthread_mutex_unlock(philo->fork);
	philo->last_time_eaten = get_time(philo->data);
	philo->times_eaten++;
	if (philo->times_eaten == philo->data->times_philo_must_eat)
		philo->data->status->all_ate = true;
	return (0);
}

void	one_philo_sleep(t_philo *philo)
{
	long long	time;

	if (philo->data->status->all_ate == true)
		return ;
	time = get_time(philo->data);
	philo->last_time_eaten = time;
	print_msg(philo, time, "is sleeping", false);
	acc_usleep(philo->data, philo->data->time_to_sleep);
}
