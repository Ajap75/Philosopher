/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:58:04 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/18 11:21:07 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

int	init_fork(t_monitor *monitor, t_philo *philo)
{
	if (init_left_fork(philo) == 1)
		return (1);
	if (monitor->veritas->nbr_philo > 1)
		init_right_fork(monitor, philo);
	return (0);
}

int	init_left_fork(t_philo *philo)
{
	if (pthread_mutex_init(&philo->mutex.lf, NULL) != 0)
		return (1);
	return (0);
}

void	init_right_fork(t_monitor *monitor, t_philo *philo)
{
	if (philo->id == monitor->veritas->nbr_philo)
		philo->mutex.rf = &monitor->philos[0].mutex.lf;
	else
		philo->mutex.rf = &monitor->philos[philo->id].mutex.lf;
}

/* keep in mind that the philosophers are stored in an array -> Ph[0].id = 1 */