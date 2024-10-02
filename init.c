/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:12:48 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/02 17:46:24 by anastruc         ###   ########.fr       */
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
	pthread_mutex_init(&monitor->mutex.is_speaking, NULL);
	pthread_mutex_init(&monitor->mutex.dead_ph, NULL);
	pthread_mutex_init(&monitor->mutex.is_sitting, NULL);
	pthread_mutex_init(&monitor->mutex.symposium_state, NULL);
	pthread_mutex_init(&monitor->mutex.has_eaten_enough, NULL);
	monitor->mutabilitas->dead_ph_id = malloc(sizeof(int));
	monitor->mutabilitas->has_eaten_enough = malloc(sizeof(int));
	monitor->mutabilitas->is_sitting = malloc(sizeof(int));
	monitor->mutabilitas->is_speaking = malloc(sizeof(int));
	monitor->mutabilitas->symposium_state = malloc(sizeof(int));




	monitor->veritas->nbr_philo = ft_atoi(argv[1]);
	monitor->veritas->time_to_die = ft_atoi(argv[2]);
	monitor->veritas->time_to_eat = ft_atoi(argv[3]);
	monitor->veritas->time_to_sleep = ft_atoi(argv[4]);
	monitor->veritas->start_time = get_time();
	set_dead_ph_id(monitor, -1);
	set_has_eaten_enough(monitor, 0);
	set_is_sitting(monitor, 0);
	set_symposium_state(monitor, -1);
	set_is_speaking(monitor, 0);

	monitor->philos = malloc(sizeof(t_philo) * monitor->veritas->nbr_philo);

	if (argc == 6)
		monitor->veritas->meal_target = ft_atoi(argv[5]);
	else
		monitor->veritas->meal_target = -1;
	pthread_create(&monitor->monitor, NULL, (void *)routine_monitor, monitor);
	return ;
}



int	init_fork(t_monitor *monitor, t_philo *philo)
{
		if( pthread_mutex_init(&philo->forks.lf, NULL) != 0)
		{
			write(1, "Mutex Initialisation error\n", 28);
			exit(EXIT_FAILURE);
		}
		printf("je suis le philo num : %d J'init une fourchette\n", philo->id);

		if (philo->id == monitor->veritas->nbr_philo)
		{
			philo->forks.rf = &monitor->philos[0].forks.lf;
			printf("je suis le philo num : %dJe passe LA une fois\n", philo->id);
		}
		else
		{
			philo->forks.rf = &monitor->philos[philo->id + 1].forks.lf;
			printf("je suis le philo num : %d Je passe ICI une fois\n", philo->id);
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
		monitor->philos[i].monitor= monitor;
		// init_fork(monitor, &monitor->philos[i]);
		i++;
	}
	i = 0;

	while(i < monitor->veritas->nbr_philo)
	{
		usleep(1000);
		if (pthread_create(&monitor->philos[i].ph, NULL, (void *)routine, &monitor->philos[i]) == 0)
			i++;
		else
			exit(EXIT_FAILURE);
	}
}

