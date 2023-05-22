/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:05:27 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/22 17:46:54 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(t_data *data)
{
	unsigned long	time;
	gettimeofday(data->tv, NULL);
	time = data->tv->tv_sec * 1000 + data->tv->tv_usec / 1000;
	return (time - data->start_time);
}
