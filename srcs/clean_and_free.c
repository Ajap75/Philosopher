/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:35:04 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/18 15:28:59 by anastruc         ###   ########.fr       */
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
			pthread_mutex_destroy(&monitor->philos[i].mutex.life);
			pthread_mutex_destroy(&monitor->philos[i].mutex.meals_eaten);
			pthread_mutex_destroy(&monitor->philos[i].mutex.last_meal_time);
			i++;
		}
	}
	pthread_mutex_destroy(&monitor->mutex.has_eaten_enough);
	pthread_mutex_destroy(&monitor->mutex.is_sitting);
	pthread_mutex_destroy(&monitor->mutex.symposium_state);
}

void	free_everything(t_monitor *monitor)
{
	int	i;

	i = 0;
	if (monitor->mutabilitas->has_eaten_enough != NULL)
		free(monitor->mutabilitas->has_eaten_enough);
	if (monitor->mutabilitas->is_sitting != NULL)
		free(monitor->mutabilitas->is_sitting);
	if (monitor->mutabilitas->symposium_state != NULL)
		free(monitor->mutabilitas->symposium_state);
	if (monitor->mutabilitas != NULL)
		free(monitor->mutabilitas);
	if (monitor->veritas != NULL)
		free(monitor->veritas);
	if (monitor->philos != NULL)
		free(monitor->philos);
}
