/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:05:17 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/23 11:27:11 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

void	set_last_meal_time(t_philo *ph, long long current_time)
{
	pthread_mutex_lock(&ph->mutex.last_meal_time);
	ph->last_meal_time = current_time;
	pthread_mutex_unlock(&ph->mutex.last_meal_time);
}

long long	get_last_meal_time(t_philo *ph)
{
	long long	tmp;

	pthread_mutex_lock(&ph->mutex.last_meal_time);
	tmp = ph->last_meal_time;
	pthread_mutex_unlock(&ph->mutex.last_meal_time);
	return (tmp);
}

void	take_right_fork_first(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex.rf);
	speak(philo, HAS_TAKEN_A_FORK);
	pthread_mutex_lock(&philo->mutex.lf);
	speak(philo, HAS_TAKEN_A_FORK);
}

void	take_left_fork_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex.lf);
	speak(philo, HAS_TAKEN_A_FORK);
	pthread_mutex_lock(philo->mutex.rf);
	speak(philo, HAS_TAKEN_A_FORK);
}

void	i_finished_lunch(t_philo *philo)
{
	philo->meals_eaten += 1;
	if (philo->meals_eaten == philo->veritas->meal_target)
	{
		pthread_mutex_lock(&philo->monitor->mutex.full);
		*philo->monitor->mutabilitas->full += 1;
		pthread_mutex_unlock(&philo->monitor->mutex.full);
	}
}
