/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:01:38 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/07 14:40:09 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "structure.h"

void	set_dead_ph_id(t_monitor *monitor, int id)
{
	usleep(1000);
	pthread_mutex_lock(&monitor->mutex.dead_ph);
	*monitor->mutabilitas->dead_ph_id = id;
	pthread_mutex_unlock(&monitor->mutex.dead_ph);
}

int	get_dead_ph_id(t_monitor *monitor)
{
	int	tmp;

	usleep(1000);
	pthread_mutex_lock(&monitor->mutex.dead_ph);
	tmp = *monitor->mutabilitas->dead_ph_id;
	pthread_mutex_unlock(&monitor->mutex.dead_ph);
	return (tmp);
}

void	set_has_eaten_enough(t_monitor *monitor, int has_eaten_enough)
{
	usleep(1000);
	pthread_mutex_lock(&monitor->mutex.has_eaten_enough);
	*monitor->mutabilitas->has_eaten_enough = has_eaten_enough;
	pthread_mutex_unlock(&monitor->mutex.has_eaten_enough);
}

int	get_has_eaten_enough(t_monitor *monitor)
{
	int	tmp;

	usleep(1000);
	pthread_mutex_lock(&monitor->mutex.has_eaten_enough);
	tmp = *monitor->mutabilitas->has_eaten_enough;
	pthread_mutex_unlock(&monitor->mutex.has_eaten_enough);
	return (tmp);
}
void	i_am_sitting(t_monitor *monitor)
{
	usleep(1000);
	pthread_mutex_lock(&monitor->mutex.is_sitting);
	*monitor->mutabilitas->is_sitting +=1;
	pthread_mutex_unlock(&monitor->mutex.is_sitting);
}

void	i_finished_lunch(t_philo *philo)
{
	usleep(1000);
	pthread_mutex_lock(&philo->forks.meals_eaten);
	philo->meals_eaten +=1;
	pthread_mutex_unlock(&philo->forks.meals_eaten);
}

int	get_meals_eaten(t_philo *philo)
{
	int tmp;
	usleep(1000);
	pthread_mutex_lock(&philo->forks.meals_eaten);
	tmp = philo->meals_eaten;
	pthread_mutex_unlock(&philo->forks.meals_eaten);
	return (tmp);
}

void	set_is_sitting(t_monitor *monitor, int is_sitting)
{
	usleep(1000);
	pthread_mutex_lock(&monitor->mutex.is_sitting);
	*monitor->mutabilitas->is_sitting = is_sitting;
	pthread_mutex_unlock(&monitor->mutex.is_sitting);
}

int	get_is_sitting(t_monitor *monitor)
{
	int	tmp;

	usleep(1000);
	pthread_mutex_lock(&monitor->mutex.is_sitting);
	tmp = *monitor->mutabilitas->is_sitting;
	pthread_mutex_unlock(&monitor->mutex.is_sitting);
	return (tmp);
}

void	set_symposium_state(t_monitor *monitor, int symposium_state)
{
	usleep(1000);
	pthread_mutex_lock(&monitor->mutex.symposium_state);
	*monitor->mutabilitas->symposium_state = symposium_state;
	pthread_mutex_unlock(&monitor->mutex.symposium_state);
}

int	get_symposium_state(t_monitor *monitor)
{
	int	tmp;

	usleep(1000);
	pthread_mutex_lock(&monitor->mutex.symposium_state);
	tmp = *monitor->mutabilitas->symposium_state;
	pthread_mutex_unlock(&monitor->mutex.symposium_state);
	return (tmp);
}

void	set_is_speaking(t_monitor *monitor, int is_speaking)
{
	usleep(1000);
	pthread_mutex_lock(&monitor->mutex.is_speaking);
	*monitor->mutabilitas->is_speaking = is_speaking;
	pthread_mutex_unlock(&monitor->mutex.is_speaking);
}

int	get_is_speaking(t_monitor *monitor)
{
	int	tmp;

	usleep(1000);
	pthread_mutex_lock(&monitor->mutex.is_speaking);
	// printf_mutex(&monitor->mutex.is_speaking);
	tmp = *monitor->mutabilitas->is_speaking;
	pthread_mutex_unlock(&monitor->mutex.is_speaking);
	return (tmp);
}
void	set_last_meal_time(t_philo *ph, long long current_time)
{
	usleep(1000);
	pthread_mutex_lock(&ph->forks.last_meal_time);
	ph->last_meal_time = current_time;
	pthread_mutex_unlock(&ph->forks.last_meal_time);
}

long long	get_last_meal_time(t_philo *ph)
{
	long long	tmp;

	usleep(1000);
	pthread_mutex_lock(&ph->forks.last_meal_time);
	tmp = ph->last_meal_time;
	pthread_mutex_unlock(&ph->forks.last_meal_time);
	return (tmp);
}



