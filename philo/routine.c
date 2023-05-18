/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:40:08 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/18 13:43:36 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	printf("\n");
	pthread_mutex_lock(philo->l_fork);
	printf("l taken by %d\n", philo->philo_no);
	sleep(1);
	// pthread_mutex_unlock(philo->l_fork);
	// pthread_mutex_lock(philo->r_fork);
	// printf("r taken by %d\n", p/hilo->philo_no);
	// sleep(1);
}

void	philo_think(void)
{
	
}

void	philo_sleep(void)
{
	
}
