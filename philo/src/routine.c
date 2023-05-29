/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:40:08 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/29 20:06:08 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*cycles(void *param)
{
	t_philo		*philo;
	t_data		*data;

	philo = param;
	data = philo->data;
	if (philo->philo_no % 2 != 0)
		usleep(100);
	while (!false)
	{
		if (data->status->someone_died == true || data->status->all_ate == true)
			break ;
		if (philo_eat(philo))
		{
			print_msg(philo, get_time(data), "died", true);
			break ;
		}
		philo_sleep(philo);
		philo_think(philo);
	}
	unlock_mutexes(philo);
	return (NULL);
}

int	philo_eat(t_philo *philo)
{
	long long	time;
	t_status	*status;

	status = philo->data->status;
	pthread_mutex_lock(philo->l_fork);
	time = get_time(philo->data);
	if (time - philo->last_time_eaten > philo->data->time_to_die)
		return (1);
	if (status->someone_died == true || status->all_ate == true)
		return (0);
	print_msg(philo, time, "has taken a fork", false);
	pthread_mutex_lock(philo->r_fork);
	time = get_time(philo->data);
	if (time - philo->last_time_eaten > philo->data->time_to_die)
		return (1);
	if (status->someone_died == true || status->all_ate == true)
		return (0);
	print_msg(philo, time, "has taken a fork", false);
	philo->is_eating = true;
	print_msg(philo, time, "is eating", false);
	acc_usleep(philo->data, philo->data->time_to_eat);
	unlock_mutexes(philo);
	return (0);
}

void	unlock_mutexes(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->last_time_eaten = get_time(philo->data);
	philo->is_eating = false;
	philo->times_eaten++;
	usleep(25);
	if (philo->times_eaten == data->times_philo_must_eat)
	{
		data->status->has_eaten_enough++;
		if (data->status->has_eaten_enough >= data->no_of_philosophers)
			data->status->all_ate = true;
	}
}

void	philo_sleep(t_philo *philo)
{
	long long	time;
	t_status	*status;

	status = philo->data->status;
	time = get_time(philo->data);
	philo->last_time_eaten = time;
	if (status->someone_died == true || status->all_ate == true)
		return ;
	print_msg(philo, time, "is sleeping", false);
	acc_usleep(philo->data, philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	long long	time;
	t_data		*data;
	t_status	*status;
	int			i;
	int			i2;

	data = philo->data;
	status = philo->data->status;
	i = philo->philo_no - 1;
	i2 = i;
	if (!i2)
		i2 = data->no_of_philosophers;
	if (data->philo[i2 - 1].is_eating
		|| data->philo[(i + 1) % data->no_of_philosophers].is_eating)
	{
		time = get_time(philo->data);
		if (status->someone_died == true || status->all_ate == true)
			return ;
		print_msg(philo, time, "is thinking", false);
	}
}
