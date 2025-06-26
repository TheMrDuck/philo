/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aswedan <aswedan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:59 by aswedan           #+#    #+#             */
/*   Updated: 2025/06/26 18:15:03 by aswedan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_sim_flag(t_info *philos_info)
{
	pthread_mutex_lock(&philos_info->timing_mutex);
	if (philos_info->simulation_flag == 0)
	{
		pthread_mutex_unlock(&philos_info->timing_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos_info->timing_mutex);
	return (0);
}

void	joining_threads(t_philo *philos, t_info *philos_info)
{
	int	i;

	i = 0;
	if (philos->info->num_of_philos == 1)
		return ;
	while (i < philos_info->num_of_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

void	forks_destroyer(t_info *philos_info, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philos_info->num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];
	t_info			*philos_info;

	if (ac < 5 || ac > 6)
	{
		write(2, "Error: Invalid number of arguments\n", 35);
		return (1);
	}
	philos_info = malloc(sizeof(t_info));
	if (!philos_info)
		return (1);
	initializer(av, philos, forks, philos_info);
	create_threads(philos, philos_info);
	joining_threads(philos, philos_info);
	pthread_mutex_destroy(&philos_info->timing_mutex);
	free(philos_info);
	return (0);
}
