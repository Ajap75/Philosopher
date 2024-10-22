/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:06:59 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/22 16:15:07 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

int	ft_usleep(size_t millisecond)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < millisecond)
	{
		usleep(1);
	}
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (((long long)current_time.tv_sec * 1000) + (current_time.tv_usec
			/ 1000));
}

int	am_i_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex.stop_flag);
	if (philo->stop_flag == 1)
	{
		pthread_mutex_unlock(&philo->mutex.stop_flag);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex.stop_flag);
	return (0);
}
