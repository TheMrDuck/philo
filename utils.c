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
static t_info	init_info(char **av)
{
	t_info	rtn;
	rtn.num_of_philos = ft_atoi(av[1]);
	rtn.time_to_die = ft_atoi(av[2]);
	rtn.time_to_eat = ft_atoi(av[3]);
	rtn.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		rtn.num_of_meals = ft_atoi(av[5]);
	else
		rtn.num_of_meals = -1;
	return(rtn);
}

void	initializer(char ** av, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	t_info philos_info;
	philos_info = init_info(av);
	while (i < philos_info.num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		philos[i].id = i + 1;
		philos[i].is_alive = 1;
		philos[i].last_meal = -1;
		philos[i].info = &philos_info;
		philos[i].r_fork = &forks[i];
		if (i == 0)
			philos[i].l_fork = &forks[philos_info.num_of_philos];
		else
			philos[i].l_fork = &forks[i - 1];
		i++;
	}
}

void create_threads (t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info -> num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
			exit_error("Thread Creating Failed!\n");
		i++;
	}
	i = 0;
	while (i < info->num_of_philos)
	{
		if(pthread_join(philo[i].thread, NULL) != 0)
			exit_error("Join Failed!\n");
		i++;
	}

}
