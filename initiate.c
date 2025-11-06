/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:50:35 by zali              #+#    #+#             */
/*   Updated: 2025/11/06 16:01:24 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_full(t_philo *philo)
{
	if (philo->data->n_eats == -1)
		return (0);
	if (philo->n_eats >= philo->data->n_eats)
		return (1);
	return (0);
}

int	philo_dead(t_philo *philo)
{
	if ((get_current_time() - philo->last_eaten)
		> (size_t)philo->data->die_time)
	{
		pthread_mutex_lock(&philo->data->mutex_stop);
		printf("\33[31m%ld\t%i\t died\33[0m\n",
			get_current_time() - philo->data->start_time, philo->id + 1);
		return (1);
	}
	return (0);
}

int	should_stop(t_data *data)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&data->philos[i].eat_mutex);
		if (philo_dead(&data->philos[i]))
		{
			pthread_mutex_unlock(&data->philos[i].eat_mutex);
			return (1);
		}
		full += philo_full(&data->philos[i]);
		pthread_mutex_unlock(&data->philos[i].eat_mutex);
		i++;
	}
	if (data->n_eats != -1 && full >= data->n_philos)
	{
		pthread_mutex_lock(&data->mutex_stop);
		return (1);
	}
	return (0);
}

void	monitor_philos(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	while (1)
	{
		if (should_stop(data))
		{
			data->stop = 1;
			pthread_mutex_unlock(&data->mutex_stop);
			break ;
		}
	}
}

int	initiate(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	while (++i < data->n_philos)
		if (safe_create_thread(&data->philos[i].thread,
				philo_routine, (void *)&data->philos[i]))
			return (clean_up_threads(data, i));
	if (safe_create_thread(&monitor, monitor_philos, (void *)data))
		return (clean_up_threads(data, i));
	if (pthread_join(monitor, NULL))
	{
		clean_up_threads(data, i);
		return (error_exit("pthread_join fail\n"));
	}
	i = -1;
	while (++i < data->n_philos)
		if (pthread_join(data->philos[i].thread, NULL))
			return (error_exit("pthread_join fail\n"));
	return (0);
}
