/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:35:56 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/17 20:15:14 by aolde-mo         ###   ########.fr       */
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
	}
	return (NULL);
}

void	ft_create_threads(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = data->philo;
	while (i < data->no_of_philosophers)
	{
		if (pthread_create(philo[i].th, NULL, &cycles, (void *)&philo[i]))
			ft_errno("error creating thread...");
		i++;
	}
	i = 0;
	while (i < data->no_of_philosophers)
	{
		if (pthread_join(*philo[i].th, NULL))
			ft_errno("error joining thread...");
		i++;
	}
}

void	ft_threads(t_data *data)
{
	ft_create_threads(data);
}
