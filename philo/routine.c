/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:40:08 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/22 18:08:45 by aolde-mo         ###   ########.fr       */
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
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	// time = get_time(philo->data);
	printf("l taken by %d\n", philo->philo_no);
	pthread_mutex_lock(philo->r_fork);
	// time = get_time(philo->data);
	printf("r taken by %d\n", philo->philo_no);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_think(void)
{
	
}

void	philo_sleep(t_philo *philo)
{
	printf("%d is sleeping\n", philo->philo_no);
	usleep(philo->data->time_to_sleep * 1000);
}
