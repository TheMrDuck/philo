/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aswedan <aswedan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:49 by aswedan           #+#    #+#             */
/*   Updated: 2025/06/10 16:18:23 by aswedan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(unsigned int	sleeping_time)
{
	unsigned int	follower;

	follower = 0;
	while(follower <= sleeping_time)
	{
		follower += 15;
		usleep(15);
	}
}
size_t	get_timestamp()
{
	struct timeval timer;

	if (gettimeofday(&timer, NULL) == -1)
		exit_error("Getting the time has failed!\n");
	return (timer.tv_sec * 1000 + timer.tv_usec / 1000);
}
