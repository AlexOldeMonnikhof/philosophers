/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:35:56 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/15 16:57:49 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*cycles(void *param)
{
	t_data *data;
	int		i;

	data = param;
	i = 0;
	
	while (!false)
	{
		printf("%d ", data->no_of_philosophers);
	}
}

void	ft_create_threads(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->no_of_philosophers)
	{
		if (pthread_create(&data->philo->th[i], NULL, &cycles, (void *)data))
			ft_errno("error creating thread...");
		i++;
	}
	i = 0;
	while (i < data->no_of_philosophers)
	{
		if (pthread_join(data->philo->th[i], NULL))
			ft_errno("error joining thread...");
		i++;
	}
}

void	ft_threads(t_data *data)
{
	ft_create_threads(data);
}
