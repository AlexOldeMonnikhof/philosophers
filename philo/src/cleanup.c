/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:34:08 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/06/07 17:36:17 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	cleanup(t_data *data)
{
	unsigned int	i;
	unsigned int	no;

	i = 0;
	no = data->no_of_philosophers;
	while (i < no)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
	free(data->philo);
	free(data->th);
	pthread_mutex_destroy(&data->writing);
	pthread_mutex_destroy(&data->check_eat_count);
	pthread_mutex_destroy(&data->die_mutex);
	pthread_mutex_destroy(&data->all_ate_mutex);
}

void	free_specific(t_data *data)
{
	if (data->th)
		free(data->th);
	if (data->philo)
		free(data->philo);
}
