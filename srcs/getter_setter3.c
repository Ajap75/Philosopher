/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:08:31 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/16 15:12:38 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

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
	usleep(10);
	int	tmp;
	pthread_mutex_lock(&monitor->mutex.symposium_state);
	tmp = *monitor->mutabilitas->symposium_state;
	pthread_mutex_unlock(&monitor->mutex.symposium_state);
	return (tmp);
}




