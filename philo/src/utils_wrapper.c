/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wrapper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakiyama  <rakiyama@student.42tokyo.j      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 21:31:14 by rakiyama          #+#    #+#             */
/*   Updated: 2021/12/24 21:31:14 by rakiyama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	gettimeofday_micro(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		put_error("gettimeofday");
		return (-1);
	}
	return (tv.tv_sec * 1000 * 1000 + tv.tv_usec);
}

t_status	do_usleep(useconds_t microseconds)
{
	long	time_now;
	long	time_end;
	long	time_left;

	time_now = gettimeofday_micro();
	if (time_now == -1)
		return (put_error("time_now"));
	time_end = time_now + microseconds;
	while (TRUE)
	{
		time_now = gettimeofday_micro();
		if (time_now == -1)
			return (put_error("time_now"));
		time_left = time_end - time_now;
		if (time_left <= 0)
			break ;
		else if (usleep(time_left / 2))
			return (put_error("usleep"));
	}
	return (SUCCESS);
}

long	gettimeofday_mili(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		put_error("gettimeofday");
		return (-1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	thre_create(pthread_t *thread, \
				void *(*start_routine)(void *), \
						void *arg, char *message)
{
	int	ret;

	ret = pthread_create(thread, NULL, start_routine, arg);
	if (ret)
	{
		ft_putstr_fd("error: pthread_create: ", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (ret);
}

int	thre_join(pthread_t thread, char *message)
{
	int	ret;

	ret = pthread_join(thread, NULL);
	if (ret)
	{
		ft_putstr_fd("error: pthread_join: ", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (ret);
}
