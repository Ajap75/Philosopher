/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:15:29 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/18 12:36:44 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

void	*routine_monitor(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	while (1)
	{
		if (is_everybody_sitting(monitor) == 1)
			break ;
	}
	while (1)
	{
		if (get_symposium_state(monitor) == 1)
		{
			if (monitor->veritas->meal_target != -1)
			{
				who_has_eaten_enough(monitor);
			}
			who_has_died(monitor);
		}
		else
			return ((void *)(NULL));
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
			speak(&monitor->philos[i], DEAD);
			return (0);
		}
		i++;
	}
	return (0);
}

void	who_has_eaten_enough(t_monitor *monitor)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (get_fed_philos_count(monitor) == monitor->veritas->nbr_philo)
	{
		set_symposium_state(monitor, -1);
		return ;
	}
	while (i < monitor->veritas->nbr_philo)
	{
		if (get_meals_eaten(&monitor->philos[i]) >= monitor->veritas->meal_target)
			j++;
		i++;
	}
	update_fed_philos_count(monitor, j);
}

int	is_everybody_sitting(t_monitor *monitor)
{
	int	i;

	i = 0;
	if (get_is_sitting(monitor) == monitor->veritas->nbr_philo)
	{
		monitor->veritas->start_time = get_time();
		while (i < monitor->veritas->nbr_philo)
		{
			monitor->philos[i].last_meal_time = monitor->veritas->start_time;
			i++;
		}
		set_symposium_state(monitor, 1);
		return (1);
	}
	return (0);
}
