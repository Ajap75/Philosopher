/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:01:38 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/16 14:10:20 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"


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


