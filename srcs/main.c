/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:48:08 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/18 11:32:59 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

void	join_threads(t_monitor *monitor)
{
	int	i;

	i = 0;
	pthread_join(monitor->monitor, NULL);
	while (i < monitor->veritas->nbr_philo)
	{
		pthread_join(monitor->philos[i].ph, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_monitor	monitor;
	int			i;

	i = 0;
	if ((parsing(argc, argv)))
		return (1);
	if (init_monitor(&monitor, argc, argv) == 1 || init_philos(&monitor) == 1)
	{
		clean(&monitor);
		return (1);
	}
	join_threads(&monitor);
	clean(&monitor);
	return (0);
}
