/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:53:13 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/06/12 14:27:57 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*one_philo_cycle(void *param)
{
	t_philo	*philo;
	t_data	*data;

	philo = param;
	data = philo->data;
	pthread_mutex_lock(philo->data->forks);
	print_msg(philo, get_time(data), "has taken a fork", false);
	acc_usleep(data, data->time_to_die);
	print_msg(philo, get_time(data), "died", true);
	pthread_mutex_unlock(philo->data->forks);
	return (NULL);
}
