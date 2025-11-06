/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:50:40 by zali              #+#    #+#             */
/*   Updated: 2025/11/06 15:48:10 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (display_status(philo, " has taken a fork\n")
		|| philo->data->n_philos == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	if (display_status(philo, " has taken a fork\n")
		|| display_status(philo, " is eating\n"))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(&philo->eat_mutex);
	philo->n_eats++;
	philo->last_eaten = get_current_time();
	pthread_mutex_unlock(&philo->eat_mutex);
	ft_usleep(philo->data, philo->data->eat_time);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
	{
		display_status(philo, " is thinking\n");
		ft_usleep(philo->data, 1);
	}
	while (1)
	{
		eat(philo);
		if (philo->data->n_philos == 1
			|| display_status(philo, " is sleeping\n"))
			break ;
		ft_usleep(philo->data, philo->data->sleep_time);
		if (philo->data->n_philos == 1
			|| display_status(philo, " is thinking\n"))
			break ;
	}
}

static int	fail_mutex_handler(t_data *data, int idx_last_eat_mutex)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mutex_stop);
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		if (i < idx_last_eat_mutex)
			pthread_mutex_destroy(&data->philos[i].eat_mutex);
		i++;
	}
	return (error_exit("eat mutex fail\n"));
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].data = data;
		data->philos[i].n_eats = 0;
		data->philos[i].id = i;
		data->philos[i].last_eaten = get_current_time();
		data->philos[i].l_fork = &data->forks[i];
		if (i == 0)
			data->philos[i].r_fork = &data->forks[data->n_philos - 1];
		else
			data->philos[i].r_fork = &data->forks[i - 1];
		if (pthread_mutex_init(&data->philos[i].eat_mutex, NULL))
			return (fail_mutex_handler(data, i));
		i++;
	}
	return (0);
}
