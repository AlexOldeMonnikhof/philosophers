/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:40:08 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/23 19:33:11 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*cycles(void *param)
{
	t_philo	*philo;

	philo = param;
	if (philo->philo_no % 2 != 0)
		usleep(100);
	while (!false)
	{
		if (philo_eat(philo))
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			philo_think(philo);
			break ;
		}
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	philo_eat(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(philo->l_fork);
	time = get_time(philo->data);
	printf("%lld %d has taken a fork\n", time, philo->philo_no);
	pthread_mutex_lock(philo->r_fork);
	time = get_time(philo->data);
	printf("%lld %d has taken a fork\n", time, philo->philo_no);
	philo->is_eating = true;
	printf("%lld %d is eating\n", time, philo->philo_no);
	acc_usleep(philo->data, philo->data->time_to_eat);
	philo->times_eaten++;
	if (philo->times_eaten == philo->data->times_philo_must_eat)
		return (1);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->is_eating = false;
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	long long	time;

	time = get_time(philo->data);
	printf("%lld %d is sleeping\n", time, philo->philo_no);
	acc_usleep(philo->data, philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	long long	time;
	t_data		*data;
	int			i;
	int			i2;
	int			no;

	data = philo->data;
	i = philo->philo_no - 1;
	no = data->no_of_philosophers;
	i2 = i;
	if (!i2)
		i2 = no;
	usleep(100);
	if (data->philo[i2 - 1].is_eating || data->philo[(i + 1) % no].is_eating)
	{
		time = get_time(philo->data);
		printf("%lld %d is thinking\n", time, philo->philo_no);
	}
}
