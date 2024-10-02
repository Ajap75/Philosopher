/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:01:38 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/02 17:40:16 by anastruc         ###   ########.fr       */
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
void	ask_the_mic(t_monitor *monitor)
{
		usleep(1000);
		pthread_mutex_lock(&monitor->mutex.is_speaking);
		*monitor->mutabilitas->is_speaking = 1;
}
void	give_the_mic_back(t_monitor *monitor)
{
		usleep(1000);
		*monitor->mutabilitas->is_speaking = 0;
		pthread_mutex_unlock(&monitor->mutex.is_speaking);

}

