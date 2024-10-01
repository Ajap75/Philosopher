/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:12:48 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/01 18:06:54 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "function.h"


int	get_time()
{
	struct timeval current_time ;
	gettimeofday(&current_time, NULL);
	return (current_time.tv_usec);
}

void init_monitor(t_monitor *monitor, int argc, char *argv[])
{
	monitor->veritas = malloc(sizeof(t_veritas));
	monitor->mutabilitas = malloc(sizeof(t_mutabilitas));
	monitor->mutabilitas->dead_ph_id = malloc(sizeof(int));
	monitor->mutabilitas->has_eaten_enough = malloc(sizeof(int));
	monitor->mutabilitas->is_sitting = malloc(sizeof(int));
	monitor->mutabilitas->is_speaking = malloc(sizeof(int));
	monitor->mutabilitas->symposium_state = malloc(sizeof(int));




	pthread_create(&monitor->monitor, NULL, (void *)routine_monitor, monitor);
	pthread_mutex_init(&monitor->mutex.is_speaking, NULL);
	pthread_mutex_init(&monitor->mutex.dead_ph, NULL);
	pthread_mutex_init(&monitor->mutex.is_sitting, NULL);
	pthread_mutex_init(&monitor->mutex.symposium_state, NULL);
	pthread_mutex_init(&monitor->mutex.has_eaten_enough, NULL);
	monitor->veritas->nbr_philo = ft_atoi(argv[1]);
	monitor->veritas->time_to_die = ft_atoi(argv[2]);
	monitor->veritas->time_to_eat = ft_atoi(argv[3]);
	monitor->veritas->time_to_sleep = ft_atoi(argv[4]);
	monitor->veritas->start_time = get_time();
	*monitor->mutabilitas->dead_ph_id = -1;
	*monitor->mutabilitas->has_eaten_enough = 0;
	*monitor->mutabilitas->is_sitting = 0;
	*monitor->mutabilitas->symposium_state = -1;


	monitor->philos = malloc(sizeof(t_philo) * monitor->veritas->nbr_philo);

	if (argc == 6)
		monitor->veritas->meal_target = ft_atoi(argv[5]);
	else
		monitor->veritas->meal_target = -1;
	return ;
}



int	init_fork(t_monitor *monitor, t_philo *philo)
{
		if( pthread_mutex_init(&philo->forks.lf, NULL) != 0)
		{
			write(1, "Mutex Initialisation error\n", 28);
			exit(EXIT_FAILURE);
		}
		printf("J'init une fourchette\n");

		if (philo->id == monitor->veritas->nbr_philo)
		{
			philo->forks.rf = &monitor->philos[0].forks.lf;
			printf("Je passe LA une fois\n");
		}
		else
		{
			philo->forks.rf = &monitor->philos[philo->id + 1].forks.lf;
			printf("Je passe ICI une fois\n");
		}

	return(0);
}


void	init_philos(t_monitor *monitor)
{
	int i;

	i = 0;

	while(i < monitor->veritas->nbr_philo)
	{
		monitor->philos[i].id = i + 1;
		monitor->philos[i].meals_eaten = 0;
		monitor->philos[i].last_meal_time = 0;
		monitor->philos[i].status = 0;
		monitor->philos[i].meals_eaten = 0;
		monitor->philos[i].veritas = malloc(sizeof(t_veritas));
		monitor->philos[i].veritas= monitor->veritas;
		monitor->philos[i].monitor = malloc(sizeof(t_monitor));
		monitor->philos[i].monitor= monitor;
		// init_fork(monitor, &monitor->philos[i]);
		i++;
	}
	i = 0;

	while(i < monitor->veritas->nbr_philo)
	{
		if (pthread_create(&monitor->philos[i].ph, NULL, (void *)routine, &monitor->philos[i]) == 0)
		{
			i++;
			printf("Je me suis cree : thread\n");
		}
	}
}

