/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:48:35 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/09 17:28:39 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct data{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}		t_data;

typedef struct philo{
	t_data		*data;
	pthread_t	thread;
	int			philo_no;
}				t_philo;

void	parse_atoi(t_data *data, int argc, char **argv);
void	parse_correct_arguments(t_data *data, int ms, int i);
void	ft_parse(t_data *data, int argc, char **argv);

void	ft_check(int argc, char **argv);
void	check_argv(char **argv);

void	ft_error(char *msg);
void	ft_errno(char *msg);

int		ft_atoi_data(const char *str);

#endif