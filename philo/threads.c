/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:35:56 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/09 16:41:39 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_threads(t_philo *philo, int argc, int thread_amount)
{
	int			i;
	pthread_t	th[thread_amount];

	i = 0;
	while (i < thread_amount)
	{
		if (!pthread_create(th + i, NULL, &asd, NULL))
			ft_errno("error creating thread...");
	}
}

void	ft_threads(t_philo *philo, int argc)
{
	ft_create_threads(philo, argc, philo->number_of_philosophers);
}
