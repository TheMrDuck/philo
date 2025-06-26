/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aswedan <aswedan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:59 by aswedan           #+#    #+#             */
/*   Updated: 2025/06/10 15:50:02 by aswedan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_error(char *msg)
{
	printf("%s", msg);
	exit(1);
}

int main(int ac, char **av)
{
	t_philo philos[PHILO_MAX];
	pthread_mutex_t forks[PHILO_MAX];
	t_info *philos_info;
	int i;

	if (ac < 5 || ac > 6)
		exit_error("Wrong number of arguments\n");
	
	philos_info = malloc(sizeof(t_info));
	if (!philos_info)
		exit_error("Memory allocation failed\n");
	
	initializer(av, philos, forks, philos_info);
	create_threads(philos, philos_info);
	
	i = 0;
	while (i < philos_info->num_of_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	
	i = 0;
	while (i < philos_info->num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philos_info->timing_mutex);
	
	free(philos_info);
	return (0);
}

