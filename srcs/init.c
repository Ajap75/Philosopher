/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:12:48 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/22 16:11:58 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

int	init_monitor(t_monitor *monitor, int argc, char *argv[])
{
	if (ft_malloc(monitor) == 1)
		return (print_error_message(MALLOC_ERROR), 1);
	if (init_monitor_mutex(monitor) == 1)
		return (print_error_message(MUTEX_INIT_ERROR), 1);
	monitor->veritas->nbr_philo = ft_atol(argv[1]);
	monitor->veritas->time_to_die = ft_atol(argv[2]);
	monitor->veritas->time_to_eat = ft_atol(argv[3]);
	monitor->veritas->time_to_sleep = ft_atol(argv[4]);
	monitor->veritas->start_time = get_time() + 500;
	*monitor->mutabilitas->full = 0;
	*monitor->mutabilitas->stop_flag = 0;
	monitor->philos = malloc(sizeof(t_philo) * monitor->veritas->nbr_philo);
	if (monitor->philos == NULL)
		return (print_error_message(MALLOC_ERROR), 1);
	if (argc == 6)
		monitor->veritas->meal_target = ft_atol(argv[5]);
	else
		monitor->veritas->meal_target = -1;
	return (0);
}

int	init_philos(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->veritas->nbr_philo)
	{
		monitor->philos[i].id = i + 1;
		monitor->philos[i].meals_eaten = 0;
		monitor->philos[i].last_meal_time = monitor->veritas->start_time;
		monitor->philos[i].statut = 0;
		monitor->philos[i].stop_flag = 0;
		monitor->philos[i].meals_eaten = 0;
		monitor->philos[i].veritas = monitor->veritas;
		monitor->philos[i].monitor = monitor;
		if (init_philo_mutex(monitor, i) == 1 || init_fork(monitor,
				&monitor->philos[i]) == 1)
			return (1);
		i++;
	}
	i = 0;
	return (0);
}

int	init_philo_thread(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->veritas->nbr_philo)
	{
		if (pthread_create(&monitor->philos[i].ph, NULL, (void *)routine,
				&monitor->philos[i]) == 0)
			i++;
		else
			return (print_error_message(THREAD_INIT), 1);
	}
	return (0);
}

int	init_philo_mutex(t_monitor *monitor, int i)
{
	if (pthread_mutex_init(&monitor->philos[i].mutex.last_meal_time, NULL) != 0
		|| pthread_mutex_init(&monitor->philos[i].mutex.stop_flag, NULL) != 0)
		return (1);
	return (0);
}

int	init_monitor_mutex(t_monitor *monitor)
{
	if (pthread_mutex_init(&monitor->mutex.full, NULL) != 0
		|| pthread_mutex_init(&monitor->mutex.speak, NULL) != 0)
		return (1);
	return (0);
}
