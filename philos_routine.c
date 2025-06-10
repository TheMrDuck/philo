#include "philo.h"

void	is_eating(t_philo	*philo)
{
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->r_fork);
	printf("%d is eating...\n", philo->id);
	usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

void	is_thinking(t_philo *philo)
{
	printf("%d is thinking...\n", philo->id);
}

void	is_sleeping(t_philo *philo)
{
	printf("%d is sleeping...\n", philo->id);
	usleep(philo->info->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*local_philo;

	local_philo = (t_philo*) arg;
	while (local_philo->is_alive)
	{
		is_eating(local_philo);
		is_sleeping(local_philo);
		is_thinking(local_philo);
	}
	return (NULL);
}


