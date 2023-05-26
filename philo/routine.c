/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:40:08 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/26 20:12:23 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*cycles(void *param)
{
	t_philo		*philo;
	t_data		*data;

	philo = param;
	data = philo->data;
	if (philo->philo_no % 2 != 0)
		usleep(200);
	while (!false)
	{
		if (data->status->someone_died == true || data->status->all_ate == true)
			break ;
		if (philo_eat(philo) && data->status->someone_died == false)
		{
			data->status->someone_died = true;
			printf("%lld %d died\n", get_time(data), philo->philo_no);
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
	long long	cur_time;
	t_status	*status;

	status = philo->data->status;
	pthread_mutex_lock(philo->l_fork);
	cur_time = get_time(philo->data);
	if (cur_time - philo->last_time_eaten > philo->data->time_to_die)
		return (1);
	usleep(10);
	if (status->someone_died == true || status->all_ate == true)
		return (0);
	printf("%lld %d has taken a fork\n", cur_time, philo->philo_no);
	pthread_mutex_lock(philo->r_fork);
	cur_time = get_time(philo->data);
	if (cur_time - philo->last_time_eaten > philo->data->time_to_die)
		return (1);
	if (status->someone_died == true || status->all_ate == true)
		return (0);
	printf("%lld %d has taken a fork\n", cur_time, philo->philo_no);
	philo->is_eating = true;
	printf("%lld %d is eating\n", cur_time, philo->philo_no);
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
	if (philo->times_eaten == data->times_philo_must_eat)
	{
		data->status->has_eaten_enough++;
		if (data->status->has_eaten_enough == data->no_of_philosophers)
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
	usleep(100);
	if (status->someone_died == true || status->all_ate == true)
		return ;
	printf("%lld %d is sleeping\n", time, philo->philo_no);
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
		if (status->someone_died == true || status->all_ate == true)
			return ;
		time = get_time(philo->data);
		printf("%lld %d is thinking\n", time, philo->philo_no);
	}
}
