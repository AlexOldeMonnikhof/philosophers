/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:48:35 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/22 18:05:52 by aolde-mo         ###   ########.fr       */
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
# include <limits.h>
# include <stdbool.h>

typedef struct philo	t_philo;
typedef struct forks	t_forks;

typedef struct data{
	unsigned int	no_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	no_of_times_each_philosopher_must_eat;
	unsigned long	start_time;
	struct timeval	*tv;
	pthread_t		*th;
	t_philo			*philo;
}			t_data;

typedef struct philo{
	int				philo_no;
	t_data			*data;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}					t_philo;

// typedef struct forks{
// 	pthread_mutex_t	*l_fork;
// 	pthread_mutex_t	*r_fork;
// }					t_forks;

void	parse_data(t_data *data, int argc, char **argv);
void	parse_correct_arguments(t_data *data, int ms, int i);
void	ft_parse(t_data *data, int argc, char **argv);
void	parse_philo(t_data *data);
void	parse_mutex(t_data *data);

void	ft_check(int argc, char **argv);
void	check_argv(char **argv);

void	ft_error(char *msg);
void	ft_errno(char *msg);

int		ft_atoi_data(const char *str);

void	ft_create_threads(t_data *data);
void	ft_threads(t_data *data);

//ROUTINE
void	*cycles(void *param);
void	philo_eat(t_philo *philo);
void	philo_think(void);
void	philo_sleep(t_philo *philo);

//TIME
unsigned long	get_time(t_data *data);

#endif