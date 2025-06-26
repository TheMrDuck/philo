/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aswedan <aswedan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:50:11 by aswedan           #+#    #+#             */
/*   Updated: 2025/06/26 16:21:43 by aswedan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	picking_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
	}
}

void	is_eating(t_philo *philo)
{
	size_t	current_time;

	picking_forks(philo);
	pthread_mutex_lock(&philo->info->timing_mutex);
	current_time = get_timestamp();
	if (philo->info->simulation_flag)
		printf("%zu %d has taken a fork\n",
			(current_time - philo->info->timestamp), philo->id);
	if (philo->info->simulation_flag)
		printf("%zu %d is eating\n",
			(current_time - philo->info->timestamp), philo->id);
	philo->last_meal = current_time;
	philo->num_of_meals_eaten++;
	pthread_mutex_unlock(&philo->info->timing_mutex);
	ft_usleep(philo->info->time_to_eat, philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	is_sleeping(t_philo *philo)
{
	size_t	current_time;

	pthread_mutex_lock(&philo->info->timing_mutex);
	current_time = get_timestamp();
	if (philo->info->simulation_flag)
		printf("%zu %d is sleeping\n",
			(current_time - philo->info->timestamp), philo->id);
	pthread_mutex_unlock(&philo->info->timing_mutex);
	ft_usleep(philo->info->time_to_sleep, philo);
}

void	is_thinking(t_philo *philo)
{
	size_t	current_time;

	pthread_mutex_lock(&philo->info->timing_mutex);
	current_time = get_timestamp();
	if (philo->info->simulation_flag)
		printf("%zu %d is thinking\n",
			(current_time - philo->info->timestamp), philo->id);
	pthread_mutex_unlock(&philo->info->timing_mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->time_to_eat / 2, philo);
	while (1)
	{
		if (check_sim_flag(philo->info))
			return (NULL);
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}
