/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aswedan <aswedan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:15:02 by aswedan           #+#    #+#             */
/*   Updated: 2025/06/26 15:56:03 by aswedan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define PHILO_MAX 200

typedef struct s_info
{
    int				num_of_philos;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				num_of_meals;
    size_t			timestamp;
    int				simulation_flag;
    int             meals_completed;
    pthread_mutex_t	timing_mutex;
}	t_info;

typedef struct s_philo
{
    int				id;
    size_t			last_meal;
    int				is_alive;
    int				num_of_meals_eaten;
    pthread_t		thread;
    t_info*			info;
    pthread_mutex_t	*r_fork;
    pthread_mutex_t	*l_fork;
}	t_philo;


void	exit_error(char *str);
t_info	init_info(char **av);
void	initializer(char **av, t_philo *philos, pthread_mutex_t *forks, t_info *philos_info);
void	create_threads(t_philo *philos, t_info *info);
void	*routine(void *arg);
size_t	get_timestamp(void);
void	death_monitor(t_philo *philos);
void	ft_usleep(size_t milliseconds, t_philo *philos);
int check_sim_flag(t_info *philos_info);

#endif
