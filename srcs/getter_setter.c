/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:01:38 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/16 11:51:41 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

// getter and setter are usefull especially when you want to check a value in an if condition


void	set_has_eaten_enough(t_monitor *monitor, int has_eaten_enough)
{
	ft_usleep(1);
	pthread_mutex_lock(&monitor->mutex.has_eaten_enough);
	*monitor->mutabilitas->has_eaten_enough = has_eaten_enough;
	pthread_mutex_unlock(&monitor->mutex.has_eaten_enough);
}


void	update_fed_philos_count(t_monitor *monitor, int i)
{
	pthread_mutex_lock(&monitor->mutex.has_eaten_enough);
	*monitor->mutabilitas->has_eaten_enough = i;
	pthread_mutex_unlock(&monitor->mutex.has_eaten_enough);
}

int	get_fed_philos_count(t_monitor *monitor)
{
	int	tmp;

	pthread_mutex_lock(&monitor->mutex.has_eaten_enough);
	tmp = *monitor->mutabilitas->has_eaten_enough;
	pthread_mutex_unlock(&monitor->mutex.has_eaten_enough);
	return (tmp);
}
void	i_am_sitting(t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->mutex.is_sitting);
	*monitor->mutabilitas->is_sitting +=1;
	pthread_mutex_unlock(&monitor->mutex.is_sitting);
}

void	i_finished_lunch(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex.meals_eaten);
	philo->meals_eaten +=1;
	pthread_mutex_unlock(&philo->mutex.meals_eaten);
}

int	get_meals_eaten(t_philo *philo)
{
	int tmp;
	ft_usleep(1);
	pthread_mutex_lock(&philo->mutex.meals_eaten);
	tmp = philo->meals_eaten;
	pthread_mutex_unlock(&philo->mutex.meals_eaten);
	return (tmp);
}

void	set_is_sitting(t_monitor *monitor, int is_sitting)
{
	ft_usleep(1);
	pthread_mutex_lock(&monitor->mutex.is_sitting);
	*monitor->mutabilitas->is_sitting = is_sitting;
	pthread_mutex_unlock(&monitor->mutex.is_sitting);
}

int	get_is_sitting(t_monitor *monitor)
{
	int	tmp;

	ft_usleep(1);
	pthread_mutex_lock(&monitor->mutex.is_sitting);
	tmp = *monitor->mutabilitas->is_sitting;
	pthread_mutex_unlock(&monitor->mutex.is_sitting);
	return (tmp);
}

void	set_symposium_state(t_monitor *monitor, int symposium_state)
{
	pthread_mutex_lock(&monitor->mutex.symposium_state);
	*monitor->mutabilitas->symposium_state = symposium_state;
	pthread_mutex_unlock(&monitor->mutex.symposium_state);
}

int	get_symposium_state(t_monitor *monitor)
{
	int	tmp;
	pthread_mutex_lock(&monitor->mutex.symposium_state);
	tmp = *monitor->mutabilitas->symposium_state;
	pthread_mutex_unlock(&monitor->mutex.symposium_state);
	return (tmp);
}

void	set_is_speaking(t_monitor *monitor, int is_speaking)
{
	pthread_mutex_lock(&monitor->mutex.is_speaking);
	*monitor->mutabilitas->is_speaking = is_speaking;
	pthread_mutex_unlock(&monitor->mutex.is_speaking);
}

int	get_is_speaking(t_monitor *monitor)
{
	int	tmp;

	pthread_mutex_lock(&monitor->mutex.is_speaking);
	// printf_mutex(&monitor->mutex.is_speaking);
	tmp = *monitor->mutabilitas->is_speaking;
	pthread_mutex_unlock(&monitor->mutex.is_speaking);
	return (tmp);
}
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


void	take_right_fork_first (t_philo *philo)
{
	pthread_mutex_lock(philo->mutex.rf);
	speak(philo, HAS_TAKEN_A_FORK);
	pthread_mutex_lock(&philo->mutex.lf);
	speak(philo, HAS_TAKEN_A_FORK);
}

void	take_left_fork_first (t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex.lf);
	speak(philo, HAS_TAKEN_A_FORK);
	pthread_mutex_lock(philo->mutex.rf);
	speak(philo, HAS_TAKEN_A_FORK);
}

int	get_life_statut(t_philo *philo)
{
	int rtn;

	pthread_mutex_lock(&philo->mutex.life);
	rtn = philo->life;
	pthread_mutex_unlock(&philo->mutex.life);
	return(rtn);
}


