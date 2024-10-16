/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:48:08 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/16 11:41:11 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

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
		printf("  How many philoophers are speaking ? = %d\n", *monitor->mutabilitas->is_speaking);
		printf("  Status of the symposium state? = %d\n", *monitor->mutabilitas->symposium_state);
		printf("  How many philosophers has eatten enough? = %d\n", *monitor->mutabilitas->has_eaten_enough);
}

int	main(int argc, char *argv[])
{
	t_monitor monitor;
	int i;

	i = 0;
	if ((parsing(argc, argv)))
		return(1);

	init_monitor(&monitor, argc, argv);
	while (1)
	{
		if (pthread_mutex_lock(&monitor.mutex.is_speaking) == 0)
		{
			printf("\n \033[0;33m*** SIMULATION CONDITIONS ***\033[0m\n");
			printf("  Number of philosopher = %d\n", monitor.veritas->nbr_philo);
			printf("  Time to die = %d\n", monitor.veritas->time_to_die);
			printf("  Time to eat = %d\n", monitor.veritas->time_to_eat);
			printf("  Time to sleep = %d\n", monitor.veritas->time_to_sleep);
			printf("  Meal goal = %d\n\n", monitor.veritas->meal_target);
			printf("  Start Time = %zu\n\n", monitor.veritas->start_time);
			printf("  Time to sleep = %d\n", monitor.veritas->time_to_sleep);
			pthread_mutex_unlock(&monitor.mutex.is_speaking);
			// print_symp_info(&monitor);
			break;
		}
	}
	init_philos(&monitor);
	join_threads(&monitor);
	print_symp_info(&monitor);
	// print_forks(&monitor);
	clean(&monitor);
	return(0);
}

// CF COMMENTAIRE DANS MONITOR THREAD
//Last meal time : Faire en sorte au'un philo ne puisse pas mourir quand il mange. Se renseigner pour savoir s'il faut update le last meal time au debut du repas et a la fin