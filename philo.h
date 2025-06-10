/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aswedan <aswedan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:15:02 by aswedan           #+#    #+#             */
/*   Updated: 2025/06/10 16:14:50 by aswedan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# define PHILO_MAX 200
typedef struct s_info
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_meals;
	int		num_of_philos;
	size_t	timestamp;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				last_meal;
	int				is_alive;
	pthread_t		thread;
	t_info*			info;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

void	initializer(char ** av, t_philo *philos, pthread_mutex_t *forks);
void	exit_error(char *msg);
void	*routine(void *arg);
void	create_threads (t_philo *philo, t_info *info);
void	ft_sleep(unsigned int	sleeping_time);
size_t	get_timestamp();
#endif
