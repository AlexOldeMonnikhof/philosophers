/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:05:27 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/30 15:28:01 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_start_time(t_data *data)
{
	gettimeofday(&data->tv, NULL);
	data->start_time = data->tv.tv_sec * 1000LL + data->tv.tv_usec / 1000LL;
}

long long	get_time(t_data *data)
{
	long long	time;

	gettimeofday(&data->tv, NULL);
	time = data->tv.tv_sec * 1000LL + data->tv.tv_usec / 1000LL;
	return (time - data->start_time);
}

void	acc_usleep(t_data *data, long long ms)
{
	long long	current_time;
	long long	placeholder;

	current_time = get_time(data);
	placeholder = current_time;
	while (current_time < placeholder + ms)
	{
		current_time = get_time(data);
		usleep(10);
	}
}
