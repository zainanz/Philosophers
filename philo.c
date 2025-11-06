/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:49:48 by zali              #+#    #+#             */
/*   Updated: 2025/11/03 13:04:45 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	pthread_mutex_t	forks[MAX_LIMIT];
	t_philo			philos[MAX_LIMIT];
	t_data			data;
	int				val;

	val = 0;
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("invalid params.\n", 2);
		ft_putstr_fd("./philo 'number_of_philosophers' 'time_to_die'"
			" 'time_to_eat' 'time_to_sleep'"
			" 'number_of_times_each_philosopher_must_eat (optional)'\n",
			2);
		return (1);
	}
	val = init_data(argv, &data, forks, philos);
	if (val == -1)
		return (0);
	if (val == 1)
		return (1);
	if (init_philos(&data) || initiate(&data))
		return (1);
	clean_up(&data);
	return (0);
}
