/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:35:56 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/23 19:33:30 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_and_join_threads(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = data->philo;
	while (i < data->no_of_philosophers)
	{
		if (pthread_create(&data->th[i], NULL, &cycles, (void *)&philo[i]))
			ft_errno("error creating thread...");
		i++;
	}
	i = 0;
	while (i < data->no_of_philosophers)
	{
		if (pthread_join(data->th[i], NULL))
			ft_errno("error joining thread...");
		i++;
	}
}
