/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aswedan <aswedan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:50:11 by aswedan           #+#    #+#             */
/*   Updated: 2025/06/10 16:16:35 by aswedan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void is_eating(t_philo *philo)
{
    size_t current_time;
    
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(philo->l_fork);
    }
    else
    {
        pthread_mutex_lock(philo->l_fork);
        pthread_mutex_lock(philo->r_fork);
    }
    pthread_mutex_lock(&philo->info->timing_mutex);
    current_time = get_timestamp();
    if (philo->info->simulation_flag)
        printf("%zu %d has taken a fork\n", (current_time - philo->info->timestamp), philo->id);
    if (philo->info->simulation_flag)
        printf("%zu %d is eating\n", (current_time - philo->info->timestamp), philo->id);
    philo->last_meal = current_time;
    philo->num_of_meals_eaten++;
    pthread_mutex_unlock(&philo->info->timing_mutex);
    ft_usleep(philo->info->time_to_eat);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

void is_thinking(t_philo *philo)
{
    size_t current_time;
    
    pthread_mutex_lock(&philo->info->timing_mutex);
    current_time = get_timestamp();
    if (philo->info->simulation_flag)
        printf("%zu %d is sleeping\n", (current_time - philo->info->timestamp), philo->id);
    pthread_mutex_unlock(&philo->info->timing_mutex);
    
    ft_usleep(philo->info->time_to_sleep);
}

void is_thinking(t_philo *philo)
{
    size_t current_time;
    
    pthread_mutex_lock(&philo->info->timing_mutex);
    current_time = get_timestamp();
    if (philo->info->simulation_flag)
        printf("%zu %d is thinking\n", (current_time - philo->info->timestamp), philo->id);
    pthread_mutex_unlock(&philo->info->timing_mutex);
}

void	*routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    if (philo->id % 2 == 0)
        ft_usleep(philo->info->time_to_eat / 2);
    
    while (philo->info->simulation_flag && philo->is_alive)
    {
        is_eating(philo);
        
        if (philo->info->num_of_meals != -1 && 
            philo->num_of_meals_eaten >= philo->info->num_of_meals)
            break;
            
        is_thinking(philo);
        is_thinking(philo);
    }
    return (NULL);
}


