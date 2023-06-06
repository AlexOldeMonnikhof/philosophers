/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:40:08 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/06/06 18:07:38 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*cycles(void *param)
{
	t_philo	*philo;
	t_data	*data;

	philo = param;
	data = philo->data;
	if (philo->philo_no % 2 != 0)
		acc_usleep(data, data->time_to_eat);
	while (check_if_died(data) == false && check_if_all_ate(data) == false)
	{
		philo_eat(philo);
		pthread_mutex_lock(&data->check_eat_count);
		if (check_if_died(data) == true && check_if_all_ate(data) == true)
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(&data->check_eat_count);
			break ;
		}
		pthread_mutex_unlock(&data->check_eat_count);
		philo_sleep_and_think(philo);
	}
	return (NULL);
}

int	philo_eat(t_philo *philo)
{
	t_data		*data;
	long long	time;

	data = philo->data;
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, get_time(data), "has taken a fork", false);
	pthread_mutex_lock(philo->r_fork);
	time = get_time(data);
	if (time - philo->last_time_eaten > philo->data->time_to_die)
	{
		print_msg(philo, time, "has died" , true);
		return (1);
	}
	print_msg(philo, time, "has taken a fork", false);
	print_msg(philo, time, "is eating", false);
	acc_usleep(data, data->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->last_time_eaten = time + philo->data->time_to_eat;
	check_eat_count(philo);
	return (0);
}

void	check_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check_eat_count);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->data->check_eat_count);
}

void	philo_sleep_and_think(t_philo *philo)
{
	long long	time;

	time = get_time(philo->data);
	print_msg(philo, time, "is sleeping", false);
	if (check_if_died(philo->data) || check_if_all_ate(philo->data))
		return ;
	acc_usleep(philo->data, philo->data->time_to_sleep);
	if (check_if_died(philo->data) || check_if_all_ate(philo->data))
		return ;
	print_msg(philo, time + philo->data->time_to_sleep, "is thinking", false);
}
