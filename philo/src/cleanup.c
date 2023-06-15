/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:34:08 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/06/08 18:46:08 by aolde-mo         ###   ########.fr       */
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
	if (data->forks)
		free(data->forks);
}

int	destroy_specific(t_data *data, int i)
{
	if (i == 0)
		return (1);
	if (i > 0)
		pthread_mutex_destroy(&data->writing);
	if (i > 1)
		pthread_mutex_destroy(&data->check_eat_count);
	if (i > 2)
		pthread_mutex_destroy(&data->die_mutex);
	return (1);
}

int	destroy_specific_forks(t_data *data, int no_of_mutexes)
{
	int	i;

	i = 0;
	destroy_specific(data, 3);
	while (i < no_of_mutexes)
		pthread_mutex_destroy(&data->forks[i++]);
	return (1);
}
