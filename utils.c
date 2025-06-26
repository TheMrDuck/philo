/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aswedan <aswedan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:50:19 by aswedan           #+#    #+#             */
/*   Updated: 2025/06/26 15:45:10 by aswedan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	c;
	int	n;
	int	r;

	c = 0;
	n = 1;
	r = 0;
	while (nptr[c] == ' ' || (nptr[c] >= 9 && nptr[c] <= 13))
		c++;
	if (nptr[c] == '-' || nptr[c] == '+')
	{
		if (nptr[c] == '-')
			n *= -1;
		c++;
	}
	while (nptr[c] >= '0' && nptr[c] <= '9')
	{
		r = (nptr[c] - '0') + (r * 10);
		c++;
	}
	return (r * n);
}
t_info	init_info(char **av)
{
	t_info	rtn;
	rtn.num_of_philos = ft_atoi(av[1]);
	rtn.time_to_die = ft_atoi(av[2]);
	rtn.time_to_eat = ft_atoi(av[3]);
	rtn.time_to_sleep = ft_atoi(av[4]);
	rtn.timestamp = get_timestamp();
	rtn.simulation_flag = 1;
	rtn.meals_completed = 0;
	if (av[5])
		rtn.num_of_meals = ft_atoi(av[5]);
	else
		rtn.num_of_meals = -1;
	return(rtn);
}

void	initializer(char **av, t_philo *philos, pthread_mutex_t *forks, t_info *philos_info)
{
    int	i;

    *philos_info = init_info(av);

    pthread_mutex_init(&philos_info->timing_mutex, NULL);

    i = 0;
    while (i < philos_info->num_of_philos)
    {
        pthread_mutex_init(&forks[i], NULL);
        philos[i].id = i + 1;
        philos[i].last_meal = philos_info->timestamp;
        philos[i].num_of_meals_eaten = 0;
        philos[i].info = philos_info;
        philos[i].r_fork = &forks[i];
        if (i == 0)
            philos[i].l_fork = &forks[philos_info->num_of_philos - 1];
        else
            philos[i].l_fork = &forks[i - 1];
        i++;
    }
}

void	create_threads(t_philo *philos, t_info *info)
{
    int i;

    i = 0;
	if (info->num_of_philos == 1)
	{
		ft_usleep(info->time_to_die);
		printf("%d %d died\n", info->time_to_die, 1);
		return;
	}
    while (i < info->num_of_philos)
    {
        if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
            exit_error("Thread creation failed\n");
        i++;
    }
    death_monitor(philos);


}
