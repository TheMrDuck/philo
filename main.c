#include "philo.h"

void	exit_error(char *msg)
{
	printf(msg);
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


}
