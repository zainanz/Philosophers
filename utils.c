/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:50:30 by zali              #+#    #+#             */
/*   Updated: 2025/11/06 15:56:26 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	display_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex_stop);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->mutex_stop);
		return (1);
	}
	printf("%ld\t%i\t%s", get_current_time() - philo->data->start_time,
		philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->mutex_stop);
	return (0);
}

void	clean_up(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mutex_stop);
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].eat_mutex);
		i++;
	}
}

int	clean_up_threads(t_data *data, int erri)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->mutex_stop);
	data->stop = 1;
	pthread_mutex_unlock(&data->mutex_stop);
	if (erri == 0)
		return (1);
	while (i < erri)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	clean_up(data);
	return (1);
}

void	ft_usleep(t_data *data, size_t ms)
{
	size_t	start;

	(void) data;
	start = get_current_time();
	if (ms == 0)
		usleep(0);
	while (get_current_time() - start < ms)
	{
		pthread_mutex_lock(&data->mutex_stop);
		if (data->stop)
		{
			pthread_mutex_unlock(&data->mutex_stop);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_stop);
		usleep(500);
	}
}
