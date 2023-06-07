/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:31:51 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/06/07 16:41:34 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	monitoring(t_data *data)
{
	unsigned int	i;

	while (died(data) == false && all_ate(data) == false)
	{
		i = 0;
		while (i < data->no_of_philosophers)
		{
			pthread_mutex_lock(&data->check_eat_count);
			if (data->ate_enough == data->no_of_philosophers)
			{
				pthread_mutex_lock(&data->all_ate_mutex);
				data->all_ate = true;
				pthread_mutex_unlock(&data->all_ate_mutex);
				pthread_mutex_unlock(&data->check_eat_count);
				break ;
			}
			pthread_mutex_unlock(&data->check_eat_count);
			i++;
		}
	}
}
