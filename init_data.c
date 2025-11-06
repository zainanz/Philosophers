/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:50:44 by zali              #+#    #+#             */
/*   Updated: 2025/11/06 16:01:48 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_forks(t_data *data)
{
	int	i;
	int	failed_init;

	i = 0;
	failed_init = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			failed_init = 1;
			break ;
		}
		i++;
	}
	if (failed_init)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&data->forks[i]);
		return (1);
	}
	return (0);
}

static int	invalid_n_philos(void)
{
	ft_putstr_fd("\033[31m[ERROR]\033[0m 0-200 is the range"
		" is the test range.\n", 2);
	ft_putstr_fd("\033[33m[INFO]\033[0m \"make re limit={VAL}", 2);
	ft_putstr_fd("\" to test your value.\n", 2);
	return (1);
}

int	init_data(char **argv, t_data *data
			, pthread_mutex_t *forks, t_philo *philos)
{
	data->n_philos = get_valid_num(argv[1]);
	if (data->n_philos > MAX_LIMIT || data->n_philos == -1 || !data->n_philos)
		return (invalid_n_philos());
	if (argv[5])
	{
		data->n_eats = get_valid_num(argv[5]);
		if (data->n_eats == 0 || data->n_eats == -1)
			return (-1);
	}
	else
		data->n_eats = -1;
	data->start_time = get_current_time();
	data->philos = philos;
	data->stop = 0;
	data->forks = forks;
	if (pthread_mutex_init(&data->mutex_stop, NULL))
		return (error_exit("stop mutex fail init\n"));
	data->die_time = get_valid_num(argv[2]);
	data->eat_time = get_valid_num(argv[3]);
	data->sleep_time = get_valid_num(argv[4]);
	if (create_forks(data) || data->die_time == -1
		|| data->eat_time == -1 || data->sleep_time == -1)
		return (1);
	return (0);
}
