/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:22:26 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/06/06 18:08:11 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi_data(const char *str)
{
	int			i;
	long long	out;

	i = 0;
	out = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		out = out * 10 + (str[i] - '0');
		i++;
	}
	if (out > INT_MAX || out < 0)
		return (-1);
	return (out);
}

void	print_msg(t_philo *philo, long long ms, char *msg, bool died)
{
	pthread_mutex_lock(&philo->data->writing);
	if (died == false && check_if_died(philo->data) == false)
		printf("%lld %d %s\n", ms, philo->philo_no, msg);
	else if (check_if_died(philo->data) == false)
	{
		philo->data->someone_died = true;
		printf("%lld %d %s\n", ms, philo->philo_no, msg);
	}
	pthread_mutex_unlock(&philo->data->writing);
}
