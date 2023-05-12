/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:35:56 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/12 17:21:03 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*cycles(void *cycles)
{
	while (!false)
	{
		
	}
}


void	ft_create_threads(t_data *data, int argc)
{
	int			i;
	pthread_t	*th;

	i = 0;
	while (i < data->no_of_philosophers)
	{
		if (pthread_create(th + i, NULL, &cycles, NULL))
			ft_errno("error creating thread...");
		i++;
	}
	i =0 ;
	while (i < data->no_of_philosophers)
	{
		if (pthread_join(*(th + i), NULL))
			ft_errno("error joining thread...");
		i++;
	}
}

void	ft_threads(t_data *data, int argc)
{
	ft_create_threads(data, argc);
}
