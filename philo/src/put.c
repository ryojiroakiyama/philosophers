/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakiyama  <rakiyama@student.42tokyo.j      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 21:31:14 by rakiyama          #+#    #+#             */
/*   Updated: 2021/12/25 21:49:54 by rakiyama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_manage_data(t_manage_data *mdata)
{
	printf("manage_data:\n");
	printf("philo_num              %d\n", mdata->philo_num);
	printf("times_must_eat         %d\n", mdata->times_must_eat);
	printf("time[TO_DIE]           %ld\n", mdata->time[TO_DIE]);
	printf("time[TO_EAT]           %ld\n", mdata->time[TO_EAT]);
	printf("time[TO_SLEEP]         %ld\n", mdata->time[TO_SLEEP]);
}

void	put_thread_data(t_thread_data *pdata)
{
	printf("-----------------------------------------------\n");
	printf("order                 %d\n", pdata->order);
	printf("times_ate             %d\n", pdata->times_ate);
	printf("times_must_eat        %d\n", pdata->times_must_eat);
	printf("time[TO_DIE]          %ld\n", pdata->time[TO_DIE]);
	printf("time[TO_EAT]          %ld\n", pdata->time[TO_EAT]);
	printf("time[TO_SLEEP]        %ld\n", pdata->time[TO_SLEEP]);
	printf("time[LAST_EAT]        %ld\n", pdata->time[LAST_EAT]);
	printf("mutex[TO_RIGHT_FORK]  %p\n", pdata->mutex[TO_RIGHT_FORK]);
	printf("mutex[TO_LEFT_FORK]   %p\n", pdata->mutex[TO_LEFT_FORK]);
	printf("mutex[TO_PUT]         %p\n", pdata->mutex[TO_PUT]);
	printf("mutex[TO_LAST_EAT]    %p\n", pdata->mutex[TO_LAST_EAT]);
	printf("time_last_eat         %p\n", pdata->time_last_eat);
	printf("is_died               %p\n", pdata->is_died);
	printf("-----------------------------------------------\n");
}

t_status	put_error(char *message)
{
	ft_putstr_fd("error: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (FAIL);
}

t_status	put_arg_error(char *message)
{
	ft_putstr_fd("error: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	printf("%stype and order of arguments required:\n", GREEN);
	printf("range: 0 - INT_MAX\n");
	printf("1: philo_num\n");
	printf("2: time_to_die\n");
	printf("3: time_to_eat\n");
	printf("4: time_to_sleep\n");
	printf("5: number_of_times_each_philosopher_must_eat (is optional)\n");
	printf("%s", RESET);
	return (FAIL);
}
