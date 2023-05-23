/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:48:35 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/23 19:39:43 by aolde-mo         ###   ########.fr       */
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
	unsigned int	times_philo_must_eat;
	long long		start_time;
	struct timeval	tv;
	pthread_t		*th;
	t_philo			*philo;
}			t_data;

typedef struct philo{
	int				philo_no;
	unsigned int	times_eaten;
	bool			is_eating;
	t_data			*data;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}					t_philo;

void		parse_data(t_data *data, int argc, char **argv);
void		parse_correct_arguments(t_data *data, int ms, int i);
void		ft_parse(t_data *data, int argc, char **argv);
void		parse_philo(t_data *data);
void		parse_mutex(t_data *data);

void		arg_check(int argc, char **argv);
void		check_argv(char **argv);

void		ft_error(char *msg);
void		ft_errno(char *msg);

int			ft_atoi_data(const char *str);

void		create_and_join_threads(t_data *data);

//ROUTINE
void		*cycles(void *param);
int			philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

//TIME
long long	get_time(t_data *data);
void		acc_usleep(t_data *data, long long ms);

#endif

//ARGUMENTS IN ORDER: 1: PHILOS, 2: DIE, 3: EAT, 4: SLEEP, 5: TIMES_TO_EAT