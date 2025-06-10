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

	if (ac < 5 || ac > 6)
		exit_error("Wrong number of arguments\n");
	//initialization
	initializer(av, philos, forks);
	create_threads(philos, philos->info);
}

