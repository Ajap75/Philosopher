/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:15:29 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/22 16:13:03 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

void	*routine_monitor(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	while (get_time() < (monitor->veritas->start_time) + 5)
	{
		ft_usleep(1);
	}
	while (*monitor->mutabilitas->stop_flag == 0)
	{
		if (monitor->veritas->meal_target != -1)
			is_everybody_full(monitor);
		who_has_died(monitor);
	}
	return ((void *)(NULL));
}

int	who_has_died(t_monitor *monitor)
{
	int			i;
	long long	current_time;
	long long	last_meal_time;

	i = 0;
	current_time = get_time();
	while (i < monitor->veritas->nbr_philo)
	{
		last_meal_time = get_last_meal_time(&monitor->philos[i]);
		if ((current_time - last_meal_time >= monitor->veritas->time_to_die))
		{
			stop_flag(monitor);
			speak(&monitor->philos[i], DEAD);
			return (0);
		}
		i++;
	}
	return (0);
}

void	is_everybody_full(t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->mutex.full);
	if (*monitor->mutabilitas->full == monitor->veritas->nbr_philo)
	{
		stop_flag(monitor);
		*monitor->mutabilitas->stop_flag = 1;
	}
	pthread_mutex_unlock(&monitor->mutex.full);
}

void	stop_flag(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->veritas->nbr_philo)
	{
		pthread_mutex_lock(&monitor->philos[i].mutex.stop_flag);
		monitor->philos[i].stop_flag = 1;
		pthread_mutex_unlock(&monitor->philos[i].mutex.stop_flag);
		i++;
	}
}
