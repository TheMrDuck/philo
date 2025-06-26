/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aswedan <aswedan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:49 by aswedan           #+#    #+#             */
/*   Updated: 2025/06/10 16:18:23 by aswedan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_meals_completed(t_philo *philos, t_info *info)
{
    int i;
    int completed_meals;
    
	
    completed_meals = 0;
    i = 0;
    if (info->num_of_meals == -1)
        return (0);
    while (i < info->num_of_philos)
    {
        pthread_mutex_lock(&info->timing_mutex);
        if (philos[i].num_of_meals_eaten >= info->num_of_meals)
            completed_meals++;
        pthread_mutex_unlock(&info->timing_mutex);
        i++;
    }
    return (completed_meals == info->num_of_philos);
}

void death_monitor(t_philo *philos)
{
    size_t current_time;
    size_t last_meal_time;
    int i;
    t_info *info;
    
    info = philos[0].info;
    
    while (info->simulation_flag)
    {
        i = 0;
        while (i < info->num_of_philos && info->simulation_flag)
        {
            pthread_mutex_lock(&info->timing_mutex);
            current_time = get_timestamp();
            last_meal_time = philos[i].last_meal;
            if (current_time - last_meal_time > (size_t)info->time_to_die)
            {
                philos[i].is_alive = 0;
                info->simulation_flag = 0;
                printf("%zu %d died\n", (current_time - info->timestamp), philos[i].id);
                pthread_mutex_unlock(&info->timing_mutex);
                return;
            }
            pthread_mutex_unlock(&info->timing_mutex);
            i++;
        }
        if (check_meals_completed(philos, info))
        {
            pthread_mutex_lock(&info->timing_mutex);
            info->simulation_flag = 0;
            pthread_mutex_unlock(&info->timing_mutex);
            break;
        }
        usleep(1000);
    }
}

void	ft_usleep(size_t milliseconds)
{
    size_t start;

    start = get_timestamp();
    while ((get_timestamp() - start) < milliseconds)
        usleep(500);
}

size_t	get_timestamp()
{
	struct timeval timer;

	if (gettimeofday(&timer, NULL) == -1)
		exit_error("Getting the time has failed!\n");
	return (timer.tv_sec * 1000 + timer.tv_usec / 1000);
}
