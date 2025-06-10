#include "philo.h"

void	is_eating(t_philo	*philo)
{
	if (pthread_mutex_lock(philo->l_fork) != 0)
		exit_error("Left fork lock failed!\n");
	if (pthread_mutex_lock(philo->r_fork) != 0)
		exit_error("Right fork lock failed!\n");
	printf("%d is eating...\n", philo->id);
	usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
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
	int	eaten_meals;

	eaten_meals = 0;
	local_philo = (t_philo*) arg;
	if (local_philo -> id % 2 == 0)
		usleep(1000);
	//printf("%d of meals\n", local_philo->info->num_of_meals);
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


