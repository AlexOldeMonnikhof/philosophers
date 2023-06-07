/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:48:35 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/06/07 16:27:38 by aolde-mo         ###   ########.fr       */
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
	unsigned int	ate_enough;
	long long		start_time;
	struct timeval	tv;
	pthread_mutex_t	writing;
	pthread_mutex_t	check_eat_count;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	all_ate_mutex;
	pthread_mutex_t	*forks;
	pthread_t		*th;
	t_philo			*philo;
	bool			someone_died;
	bool			all_ate;
}			t_data;

typedef struct philo{
	int				philo_no;
	long long		last_time_eaten;
	long long		start;
	unsigned int	times_eaten;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
}					t_philo;

//MAIN
int			main(int argc, char **argv);

//CHECK
int			arg_check(int argc, char **argv);
bool		died(t_data *data);
bool		all_ate(t_data *data);

//PARSE
int			parse_all(t_data *data, char **argv);
int			parse_data(t_data *data, char **argv);
void		parse_correct_arguments(t_data *data, int ms, int i);
int			parse_philo(t_data *data);
int			parse_forks(t_data *data);

//UTILS
int			ft_atoi_data(const char *str);
void		print_msg(t_philo *philo, long long ms, char *msg, bool is_dead);

//THREADS
int			create_and_join_threads(t_data *data);
int			one_philo_thread(t_data *data);

//ROUTINE
void		*cycles(void *param);
int			philo_eat(t_philo *philo);
void		drop_forks(t_philo *philo);
void		check_eat_count(t_philo *philo);
void		philo_sleep_and_think(t_philo *philo);

//TIME
void		set_start_time(t_data *data);
long long	get_time(t_data *data);
void		acc_usleep(t_data *data, long long ms);

//CLEANUP
void		free_specific(t_data *data);
void		cleanup(t_data *data);

//ONE PHILO
void		*one_philo_cycle(void *param);
int			one_philo_eat(t_philo *philo);
void		one_philo_sleep_and_think(t_philo *philo);

//MONITORING
void		monitoring(t_data *data);

#endif

//ARGUMENTS IN ORDER: 1: PHILOS, 2: DIE, 3: EAT, 4: SLEEP, 5: TIMES_TO_EAT