/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:48:08 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/01 17:21:30 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "function.h"

// void	destroy_philos(t_monitor *monitor)
// {
// 	int i;
// 	i = 0;

// 	while (*(monitor->philos[i])
// 	{
// 		free(monitor->philos)
// 	}
// }


void	join_threads(t_monitor *monitor)
{
	int i;
	i = 0;
	pthread_join(monitor->monitor, NULL);
	while(i < monitor->veritas->nbr_philo)
	{
		pthread_join(monitor->philos[i].ph, NULL);
		i++;
	}
}
void print_symp_info(t_monitor *monitor)
{
		printf("\n \033[0;33m*** Monitor informtions ***\033[0m\n");
		printf("  How many philoophers are sitting ? = %d\n", *monitor->mutabilitas->is_sitting);
		printf("  Status of the symposium state? = %d\n", *monitor->mutabilitas->symposium_state);
		printf("  How many philosophers has eatten enough? = %d\n", *monitor->mutabilitas->has_eaten_enough);
}

int	main(int argc, char *argv[])
{
	t_monitor monitor;
	int i;

	i = 0;

	if ((parsing(argc, argv, &monitor)))
		return(1);
	init_monitor(&monitor, argc, argv);
	printf("\n \033[0;33m*** SIMULATION CONDITIONS ***\033[0m\n");
	printf("  Number of philosopher = %d\n", monitor.veritas->nbr_philo);
	printf("  Time to die = %d\n", monitor.veritas->time_to_die);
	printf("  Time to eat = %d\n", monitor.veritas->time_to_eat);
	printf("  Time to sleep = %d\n", monitor.veritas->time_to_sleep);
	printf("  Meal goal = %d\n\n", monitor.veritas->meal_target);
	printf("  Start Time = %d\n\n", monitor.veritas->start_time);
	printf("  Time to sleep = %d\n", monitor.veritas->time_to_sleep);

	print_symp_info(&monitor);


	init_philos(&monitor);
	join_threads(&monitor);
	print_symp_info(&monitor);

	// init_fork(&monitor);
	// destroy_philos(&monitor);
	// int nbr_philo;z		monitor->philos[i].forks.rf.rf = &monitor->philos[i + 1].forks.lf.lf;

	// nbr_philo = atoi(argv[1]);
	// if (argc >= 2)
	// {
	// 	init_ph(nbr_philo);



	// printf("\n \033[0;33m*** FORK STATE ***\033[0m\n");
	// while (i < monitor.veritas->nbr_philo)
	// {
	// 	printf(" Philo name :%d, left fork = %d and right fork = %d\n", monitor.philos[i].id, monitor.philos[i].forks.lf.id, *monitor.philos[i].forks.rf.id);
	// 	i++;
	// }


	write(1, "PARSING OK\n", 12);
	clean(&monitor);
	return(0);
}