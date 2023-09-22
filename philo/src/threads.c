/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:35:56 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/09/22 14:28:17 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	create_threads(t_data *data)
{
	unsigned int	i;

	i = 0;
	set_start_time(data);
	if (data->no_of_philosophers == 1)
		return (one_philo_thread(data));
	while (i < data->no_of_philosophers)
	{
		if (pthread_create(&data->th[i], NULL, &cycle, (void *)&data->philo[i]))
			break ;
		i++;
	}
	if (i != data->no_of_philosophers)
		return (detach_threads(data, i));
	if (data->times_philo_must_eat > 0)
		monitoring(data);
	return (join_threads(data));
}

int	join_threads(t_data *data)
{
	unsigned int	i;

	i = 0;
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

int	detach_threads(t_data *data, unsigned int all_threads)
{
	unsigned int	i;

	i = 0;
	while (i < all_threads)
		pthread_detach(data->th[i++]);
	return (1);
}

void	*dead_thread_fail(t_data *data)
{
	pthread_mutex_lock(&data->die_mutex);
	data->someone_died = true;
	printf("thread to check time_to_die failed\n");
	pthread_mutex_unlock(&data->die_mutex);
	return (NULL);
}
