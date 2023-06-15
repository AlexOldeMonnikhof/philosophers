/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:40:08 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/06/12 18:52:16 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*cycle(void *param)
{
	t_philo		*philo;
	t_data		*data;
	pthread_t	th;

	philo = param;
	data = philo->data;
	if (pthread_create(&th, NULL, dead_thread, philo))
		return (dead_thread_fail(data));
	if (philo->philo_no % 2 != 0)
		acc_usleep(data, data->time_to_eat);
	while (all_ate(data) == false && died(data) == false)
	{
		if (philo_eat(philo))
		{
			drop_forks(philo);
			break ;
		}
		philo_sleep_and_think(philo);
	}
	pthread_join(th, NULL);
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
	print_msg(philo, time, "has taken a fork", false);
	if (died(philo->data) || all_ate(philo->data))
		return (1);
	if (time - philo->last_time_eaten > data->time_to_die)
	{
		print_msg(philo, get_time(data), "died", true);
		return (1);
	}
	print_msg(philo, time, "is eating", false);
	pthread_mutex_lock(&philo->data->check_eat_count);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->data->check_eat_count);
	acc_usleep(data, data->time_to_eat);
	drop_forks(philo);
	philo->last_time_eaten = time;
	check_eat_count(philo);
	return (0);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	check_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check_eat_count);
	if (philo->times_eaten == philo->data->times_philo_must_eat)
		philo->data->ate_enough++;
	pthread_mutex_unlock(&philo->data->check_eat_count);
}

void	philo_sleep_and_think(t_philo *philo)
{
	long long	time;

	time = get_time(philo->data);
	if (died(philo->data) || all_ate(philo->data))
		return ;
	print_msg(philo, time, "is sleeping", false);
	acc_usleep(philo->data, philo->data->time_to_sleep);
	if (died(philo->data) || all_ate(philo->data))
		return ;
	print_msg(philo, time + philo->data->time_to_sleep, "is thinking", false);
}
