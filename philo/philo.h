/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:48:35 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/05/29 20:06:08 by aolde-mo         ###   ########.fr       */
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
typedef struct status	t_status;

typedef struct data{
	unsigned int	no_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	times_philo_must_eat;
	long long		start_time;
	struct timeval	tv;
	pthread_mutex_t	writing;
	pthread_t		*th;
	t_philo			*philo;
	t_status		*status;
}			t_data;

typedef struct philo{
	int				philo_no;
	long long		last_time_eaten;
	unsigned int	times_eaten;
	bool			is_eating;
	t_data			*data;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}					t_philo;

typedef struct status{
	unsigned int	has_eaten_enough;
	bool			all_ate;
	bool			someone_died;
}			t_status;

//MAIN
int			main(int argc, char **argv);

//CHECK
int			arg_check(int argc, char **argv);

//PARSE
int			parse_all(t_data *data, char **argv);
int			parse_data(t_data *data, char **argv);
void		parse_correct_arguments(t_data *data, int ms, int i);
int			parse_philo(t_data *data);
void		connect_forks(t_data *data);

//UTILS
int			ft_atoi_data(const char *str);
void		print_msg(t_philo *philo, long long ms, char *msg, bool died);

//THREADS
int			create_and_join_threads(t_data *data);
int			one_philo_thread(t_data *data);

//ROUTINE
void		*cycles(void *param);
int			philo_eat(t_philo *philo);
void		unlock_mutexes(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

//TIME
void		set_start_time(t_data *data);
long long	get_time(t_data *data);
void		acc_usleep(t_data *data, long long ms);

//CLEANUP
int			free_specific(t_data *data, int err);
void		cleanup(t_data *data);

//ONE PHILO
void		*one_philo_cycle(void *param);
int			one_philo_eat(t_philo *philo);
void		one_philo_sleep(t_philo *philo);
void		one_philo_think(t_philo *philo);

#endif

//ARGUMENTS IN ORDER: 1: PHILOS, 2: DIE, 3: EAT, 4: SLEEP, 5: TIMES_TO_EAT