/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:35:56 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/09 17:20:39 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_threads(t_data *data, int argc)
{
	int			i;
	pthread_t	*th;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		th = malloc(data->number_of_philosophers * sizeof(t_philo));
		if (!pthread_create(th + i, NULL, &asd, NULL))
			ft_errno("error creating thread...");
		i++;
	}
}

void	ft_threads(t_data *data, int argc)
{
	ft_create_threads(data, argc);
}
