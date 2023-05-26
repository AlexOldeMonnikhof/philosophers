/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:35:56 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/26 20:11:51 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_and_join_threads(t_data *data)
{
	unsigned int	i;
	t_philo			*philo;

	i = 0;
	philo = data->philo;
	while (i < data->no_of_philosophers)
	{
		if (pthread_create(&data->th[i], NULL, &cycles, (void *)&philo[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < data->no_of_philosophers)
	{
		if (pthread_join(data->th[i], NULL))
			return (1);
		i++;
	}
	return (0);
}
