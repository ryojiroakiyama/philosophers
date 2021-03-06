/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakiyama <rakiyama@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 21:31:14 by rakiyama          #+#    #+#             */
/*   Updated: 2021/12/27 10:29:10 by rakiyama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <libc.h>
# include <stdbool.h>

// message of philo status
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
# define FULL "is full"
# define ERR "encounter error"

// color settings
# define RED "\033[31m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"
# define BLACK "\033[30m"
# define GREEN "\033[32m"
# define WHITE "\033[37m"
# define YEELOW "\033[33m"
# define MAGENTA "\033[35m"
# define RESET "\033[0m"

# define UNSPECIFIED -1
# define MONITOR_INTERVAL 990
# define PHILO_INTERVAL 200

// status fucntions return
typedef enum e_status
{
	SUCCESS,
	FAIL
}	t_status;

// for access_*()
typedef enum e_access_mode
{
	READ,
	EDIT,
	ZERO,
	ACCESS_NUM
}	t_access_mode;

// for put_status()
typedef enum e_put_mode
{
	CONTINUE,
	END_DIE,
	END_FULL,
	END_ERROR,
	PUT_MODE_NUM
}	t_put_mode;

// for t_thread_data
typedef enum e_mutex
{
	TO_RIGHT_FORK,
	TO_LEFT_FORK,
	TO_PUT,
	TO_LAST_EAT,
	MUTEX_NUM
}	t_mutex;

// for t_thread_data
typedef enum e_time
{
	TO_DIE,
	TO_EAT,
	TO_SLEEP,
	LAST_EAT,
	TIME_NUM
}	t_time;

// for t_manage_data
typedef enum e_threads
{
	PHILOS,
	MONITORS,
	THREADS_NUM
}	t_threads;

// for t_manage_data
typedef enum e_mutexies
{
	FORKS,
	LASTEATS,
	PUTS,
	MUTEXIES_NUM
}	t_mutexies;

// for t_threads and t_mutexies
typedef enum e_array_content
{
	INDEX,
	SIZE,
	CONTENT_NUM
}	t_array_content;

// philosopher:
// 		time_last_eat = &time[LAST_EAT](it's member)
// 		is_full = &full(is's member)
// 		is_died = &mdata->die
// monitor:
// 		time_last_eat = &time[LAST_EAT](philo's member)
// 		is_full = &full(philo's member)
// 		is_died = &mdata->die
typedef struct s_thread_data
{
	pthread_t				thread_id;
	int						order;
	int						times_ate;
	int						times_must_eat;
	long					time[TIME_NUM];
	long					*time_last_eat;
	bool					full;
	bool					*is_full;
	bool					*is_died;
	pthread_mutex_t			*mutex[MUTEX_NUM];
	struct s_thread_data	*monitor;
}	t_thread_data;

// threads:
// 		philos:		philos[i] has data of No.(i+1) philo thread.
//  	monitors:	monitors[i] has data of No.(i+1) philo's monitor thread.
// mutexies:
//  	forks:		mutex for eating action.
// 					a forks mutex is shared by philo[i] and philo[i+1]
//  	lasteats:	mutex for access to time_last_eat(each thread's member)
// 					a lasteats mutex is shared by philo[i] and monitor[i]
//  	puts:		mutex for access to put_status(). is shared by all threads.
typedef struct s_manage_data
{
	int				philo_num;
	int				times_must_eat;
	long			time[TIME_NUM];
	bool			die;
	t_thread_data	*threads;
	int				threinfo[THREADS_NUM][CONTENT_NUM];
	pthread_mutex_t	*mutexies;
	int				mutexinfo[MUTEXIES_NUM][CONTENT_NUM];
}	t_manage_data;

// memory.c
t_status	set_mdata_memory(t_manage_data *mdata);
void		free_mdata_memory(t_manage_data *mdata);
// monitor.c
void		*monitor_action(void *data);
// philo.c
void		*philo_action(void *data);
// put.c
void		put_manage_data(t_manage_data *mdata);
void		put_thread_data(t_thread_data *pdata);
t_status	put_error(char *message);
t_status	put_arg_error(char *message);
// run_thread.c
t_status	run_thread(t_manage_data *mdata);
// set_thread_data.c
t_status	set_thread_data(t_manage_data *mdata);
// thread_functions.c
long		access_time_last_eat(t_thread_data *thread, t_access_mode mode);
t_status	put_status(t_thread_data *thread, char *color, \
								char *message, t_put_mode to);
// utils_wrapper.c
t_status	do_usleep(useconds_t microseconds);
long		gettimeofday_mili(void);
int			thre_create(pthread_t *thread, \
						void *(*start_routine)(void *), \
								void *arg, char *message);
int			thre_join(pthread_t thread, char *message);
// utils.c
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(char *str, bool *is_valid);

#endif
