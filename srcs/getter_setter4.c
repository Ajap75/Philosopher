/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:09:13 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/18 12:49:47 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

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
	tmp = *monitor->mutabilitas->is_speaking;
	pthread_mutex_unlock(&monitor->mutex.is_speaking);
	return (tmp);
}

void	set_is_sitting(t_monitor *monitor, int is_sitting)
{
	pthread_mutex_lock(&monitor->mutex.is_sitting);
	*monitor->mutabilitas->is_sitting = is_sitting;
	pthread_mutex_unlock(&monitor->mutex.is_sitting);
}

void	i_am_sitting(t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->mutex.is_sitting);
	*monitor->mutabilitas->is_sitting += 1;
	pthread_mutex_unlock(&monitor->mutex.is_sitting);
}
