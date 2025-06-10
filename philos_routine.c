/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aswedan <aswedan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:50:11 by aswedan           #+#    #+#             */
/*   Updated: 2025/06/10 16:16:35 by aswedan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_eating(t_philo	*philo)
{
	if (pthread_mutex_lock(philo->l_fork) != 0)
		exit_error("Left fork lock failed!\n");
	if (pthread_mutex_lock(philo->r_fork) != 0)
		exit_error("Right fork lock failed!\n");
	printf("{%zu} %d is eating...\n", (get_timestamp() - philo->info->timestamp), philo->id);
	ft_sleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	is_thinking(t_philo *philo)
{
	printf("{%zu} %d is thinking...\n", (get_timestamp() - philo->info->timestamp), philo->id);
}

void	is_sleeping(t_philo *philo)
{
	printf("{%zu} %d is sleeping...\n", (get_timestamp() - philo->info->timestamp), philo->id);
	ft_sleep(philo->info->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*local_philo;
	int	eaten_meals;

	eaten_meals = 0;
	local_philo = (t_philo*) arg;
	if (local_philo -> id % 2 == 0)
		ft_sleep(1000);
	while (local_philo->is_alive && (eaten_meals++ < local_philo->info->num_of_meals
		&& local_philo->info->num_of_meals != -1))
	{
		is_eating(local_philo);
		if (local_philo->is_alive && (eaten_meals < local_philo->info->num_of_meals
		&& local_philo->info->num_of_meals != -1))
			is_sleeping(local_philo);
		if (local_philo->is_alive && (eaten_meals < local_philo->info->num_of_meals
		&& local_philo->info->num_of_meals != -1))
			is_thinking(local_philo);
	}
	return (NULL);
}


