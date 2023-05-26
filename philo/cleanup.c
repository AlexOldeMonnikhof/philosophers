/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:34:08 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/26 19:08:39 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	unsigned int	i;
	unsigned int	no;

	i = 0;
	no = data->no_of_philosophers;
	while (i < no)
	{
		pthread_mutex_destroy(data->philo[i].fork);
		free(data->philo[i].fork);
		i++;
	}
	free(data->th);
	free(data->philo);
	free(data->status);
}

void	free_specific(t_data *data, int err)
{
	free(data->status);
	if (err < 2)
		return ;
	if (err == 2)
		free(data->th);
	else
	{
		while (err >= 3)
			free(data->philo[err-- - 3].fork);
	}
}
