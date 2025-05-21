#include "philo.h"

void create_threats (t_philo *philo)
{
	pthread_create(philo->thread, NULL, routine, philo[i]);
}
