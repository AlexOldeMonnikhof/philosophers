/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:40:08 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/06/07 17:35:03 by aolde-mo         ###   ########.fr       */
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
	while (all_ate(data) == false && died(data) == false)
	{
		philo_eat(philo);
		if (all_ate(philo->data) || died(philo->data))
			break ;
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
		print_msg(philo, time, "died", true);
		drop_forks(philo);
		return (1);
	}
	print_msg(philo, time, "has taken a fork", false);
	if (died(philo->data) || all_ate(philo->data))
		return (0);
	print_msg(philo, time, "is eating", false);
	acc_usleep(data, data->time_to_eat);
	drop_forks(philo);
	philo->last_time_eaten = time + philo->data->time_to_eat;
	philo->times_eaten++;
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
