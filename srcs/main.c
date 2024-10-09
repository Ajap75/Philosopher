/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:48:08 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/09 18:14:44 by anastruc         ###   ########.fr       */
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

	if ((parsing(argc, argv, &monitor)))
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
	print_forks(&monitor);

	write(1, "PARSING OK\n", 12);
	clean(&monitor);
	return(0);
}
void	printf_forks(pthread_mutex_t *pthread_mutex)
{
	printf("Mutex adress = %p\n", (void *)pthread_mutex);
}
void	print_forks(t_monitor *monitor)
{
	int i;
	i = 0;

	while(i < monitor->veritas->nbr_philo)
	{
		printf("\n");
		printf("la fourchette de gauche de %d est : ", monitor->philos[i].id);
		printf_forks(&monitor->philos[i].mutex.lf);
		printf("la fourchette de droite de %d est : ", monitor->philos[i].id);
		printf_forks(monitor->philos[i].mutex.rf);
		printf("\n");
		i++;
	}
}



// Faire en sorte qu'un philosopher ne plus plus manger s'il est mort. Rester surt l'idee de chaue philosopher se marque comme mort quand il meurt et verifie s'il est mort avant de manger.
// En parallele il met a jour le tableau de mort avec son ID.
// Le monitor verifie en permanence si une ID est inscrite sur ce tableau (- de 10ms) si le tblea est remplie le monitor met l'etat du symposium a -1.
// Je pense qu'en plus de bloquer le dejeuner, il faut faire en sorte que des qu'un philo
// se poser sur l'algo du passage a table des philos.
// commencer les fourchette