/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_calls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zali <zali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:50:22 by zali              #+#    #+#             */
/*   Updated: 2025/11/06 11:04:39 by zali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_exit(char *errmsg)
{
	ft_putstr_fd(errmsg, 2);
	return (1);
}

int	safe_create_thread(pthread_t *addr,
			void *routine, void *ptr)
{
	if (pthread_create(addr, NULL, routine, ptr) != 0)
	{
		ft_putstr_fd("thread create fail\n", 2);
		return (1);
	}
	return (0);
}
