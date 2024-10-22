/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:35:04 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/22 16:08:06 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

void	clean(t_monitor *monitor)
{
	destroy_mutex(monitor);
	free_everything(monitor);
}

void	destroy_mutex(t_monitor *monitor)
{
	int	i;

	i = 0;
	{
		while (i < monitor->veritas->nbr_philo)
		{
			pthread_mutex_destroy(&monitor->philos[i].mutex.lf);
			pthread_mutex_destroy(&monitor->philos[i].mutex.last_meal_time);
			i++;
		}
	}
	pthread_mutex_destroy(&monitor->mutex.full);
	pthread_mutex_destroy(&monitor->mutex.speak);
}

void	free_everything(t_monitor *monitor)
{
	int	i;

	i = 0;
	if (monitor->mutabilitas->full != NULL)
		free(monitor->mutabilitas->full);
	if (monitor->mutabilitas->stop_flag != NULL)
		free(monitor->mutabilitas->stop_flag);
	if (monitor->mutabilitas != NULL)
		free(monitor->mutabilitas);
	if (monitor->veritas != NULL)
		free(monitor->veritas);
	if (monitor->philos != NULL)
		free(monitor->philos);
}
