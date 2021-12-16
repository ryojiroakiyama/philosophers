#include "philo.h"

static void	set_options(t_manage_data *mdata, long options[OPTION_NUM])
{
	t_time	idx_time;

	mdata->philo_num = options[NUM_OF_PHILO];
	mdata->times_must_eat = options[TIMES_PHILO_MUST_EAT];
	idx_time = 0;
	while (idx_time < TIME_NUM)
	{
		mdata->time[idx_time] = 0;
		if (idx_time <= TO_SLEEP)
			mdata->time[idx_time] = options[idx_time + 1];
		idx_time++;
	}
}

t_status	set_manage_data(t_manage_data *mdata, long options[OPTION_NUM])
{
	set_options(mdata, options);
	mdata->life_flag = NO_ONE_DIED;
	mdata->philos = (t_thread_data *)malloc(sizeof(t_thread_data) * mdata->philo_num);
	if (!mdata->philos)
		return (put_error("malloc for philo thread"));
	mdata->monitors = (t_thread_data *)malloc(sizeof(t_thread_data) * mdata->philo_num);
	if (!mdata->monitors)
		return (put_error("malloc for monitor thread"));
	mdata->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * mdata->philo_num);
	if (!mdata->forks)
		return (put_error("malloc for fork mutex"));
	mdata->last_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * mdata->philo_num);
	if (!mdata->last_eat)
		return (put_error("malloc for last_eat mutex"));
	return (SUCCESS);
}

static void copy_array(long original[], long copy[], int size)
{
	int	idx;

	idx = 0;
	while (idx < size)
	{
		copy[idx] = original[idx];
		idx++;
	}
}

static void	set_thread_data_philo(t_manage_data *mdata, t_thread_data *philo, int philo_index)
{
	philo->order = philo_index + 1;
	philo->times_must_eat = mdata->times_must_eat;
	copy_array(mdata->time, philo->time, TIME_NUM);
	philo->life_flag = &(mdata->life_flag);
	if (philo_index == 0)
		philo->mutex[RIGHT_FORK] = mdata->forks + (mdata->philo_num - 1);
	else
		philo->mutex[RIGHT_FORK] = mdata->forks + (philo_index - 1);
	philo->mutex[LEFT_FORK] = mdata->forks + philo_index;
	philo->mutex[TO_PUT] = &(mdata->put);
	philo->mutex[TO_LAST_EAT] = mdata->last_eat + philo_index;
	philo->mutex[TO_LIFE_FLAG] = &(mdata->life);
	philo->time_last_eat = &(philo->time[LAST_EAT]);
	philo->monitor = mdata->monitors + philo_index;
}

static void	set_thread_data_monitor(t_thread_data *philo, t_thread_data *monitor)
{
	monitor->order = philo->order;
	monitor->times_must_eat = philo->times_must_eat;
	copy_array(philo->time, monitor->time, TIME_NUM);
	monitor->mutex[RIGHT_FORK] = NULL;
	monitor->mutex[LEFT_FORK] = NULL;
	monitor->mutex[TO_PUT] = philo->mutex[TO_PUT];
	monitor->mutex[TO_LAST_EAT] = philo->mutex[TO_LAST_EAT];
	monitor->mutex[TO_LIFE_FLAG] = philo->mutex[TO_LIFE_FLAG];
	monitor->time_last_eat = philo->time_last_eat;
	monitor->life_flag = philo->life_flag;
	monitor->monitor = NULL;
}

t_status	set_thread_data(t_manage_data *mdata)
{
	t_thread_data	*a_philo;
	int				philo_index;

	philo_index = mdata->philo_num;
	while (philo_index--)
	{
		a_philo = mdata->philos + philo_index;
		set_thread_data_philo(mdata, a_philo, philo_index);
		set_thread_data_monitor(a_philo, a_philo->monitor);
		pthread_mutex_init(mdata->forks + philo_index, NULL);
		pthread_mutex_init(mdata->last_eat + philo_index, NULL);
	}
	pthread_mutex_init(&(mdata->put), NULL);
	pthread_mutex_init(&(mdata->life), NULL);
	//philo_index = 0;
	//while (philo_index < 5)
	//{
	//	put_thread_data(mdata->philos + philo_index);
	//	philo_index++;
	//}
	//exit(0);
	return (SUCCESS);
}