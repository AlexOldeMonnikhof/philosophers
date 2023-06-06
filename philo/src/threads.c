/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:35:56 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/06/06 17:54:49 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	create_and_join_threads(t_data *data)
{
	unsigned int	i;
	t_philo			*philo;

	i = 0;
	philo = data->philo;
	set_start_time(data);
	if (data->no_of_philosophers == 1)
		return (one_philo_thread(data));
	while (i < data->no_of_philosophers)
	{
		if (pthread_create(&data->th[i], NULL, &cycles, (void *)&philo[i]))
			return (1);
		i++;
	}
	i = 0;
	if (data->no_of_philosophers != 0)
		monitoring(data);
	while (i < data->no_of_philosophers)
	{
		if (pthread_join(data->th[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	one_philo_thread(t_data *data)
{
	t_philo	*philo;

	philo = data->philo;
	if (pthread_create(&data->th[0], NULL, &one_philo_cycle, (void *)&philo[0]))
		return (1);
	if (pthread_join(data->th[0], NULL))
		return (1);
	return (0);
}
