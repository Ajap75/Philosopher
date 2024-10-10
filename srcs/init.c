/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:12:48 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/10 12:09:33 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"



void	init_monitor(t_monitor *monitor, int argc, char *argv[])
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
	monitor->veritas->nbr_philo = ft_atol(argv[1]);
	monitor->veritas->time_to_die = ft_atol(argv[2]);
	monitor->veritas->time_to_eat = ft_atol(argv[3]);
	monitor->veritas->time_to_sleep = ft_atol(argv[4]);
	monitor->veritas->start_time = 0;
	set_dead_ph_id(monitor, -1);
	set_has_eaten_enough(monitor, 0);
	set_is_sitting(monitor, 0);
	set_symposium_state(monitor, -1);
	set_is_speaking(monitor, 0);
	monitor->philos = malloc(sizeof(t_philo) * monitor->veritas->nbr_philo);
	if (argc == 6)
		monitor->veritas->meal_target = ft_atol(argv[5]);
	else
		monitor->veritas->meal_target = -1;
	pthread_create(&monitor->monitor, NULL, (void *)routine_monitor, monitor);
	return ;
}
void	init_fork(t_monitor *monitor, t_philo *philo)
{
	init_left_fork(philo);
	if (monitor->veritas->nbr_philo > 1)
		init_right_fork(monitor, philo);

}

void	init_left_fork(t_philo *philo)
{
	pthread_mutex_init(&philo->mutex.lf, NULL);
}
void	init_right_fork(t_monitor *monitor, t_philo *philo)
{
	if (philo->id == monitor->veritas->nbr_philo)
		philo->mutex.rf = &monitor->philos[0].mutex.lf;
	else
		philo->mutex.rf = &monitor->philos[philo->id].mutex.lf;
	// keep in mind that the philosophers are stored in an array -> Ph[0].id = 1
}

void	init_philos(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->veritas->nbr_philo)
	{
		monitor->philos[i].id = i + 1;
		monitor->philos[i].life = ALIVE;
		monitor->philos[i].meals_eaten = 0;
		monitor->philos[i].last_meal_time = monitor->veritas->start_time;
		monitor->philos[i].status = 0;
		monitor->philos[i].meals_eaten = 0;
		monitor->philos[i].veritas = monitor->veritas;
		monitor->philos[i].monitor = monitor;
		pthread_mutex_init(&monitor->philos[i].mutex.last_meal_time, NULL);
		pthread_mutex_init(&monitor->philos[i].mutex.meals_eaten, NULL);
		pthread_mutex_init(&monitor->philos[i].mutex.life, NULL);
		init_fork(monitor, &monitor->philos[i]);
		i++;
	}
	i = 0;
	while (i < monitor->veritas->nbr_philo)
	{
		ft_usleep(500);
		if (pthread_create(&monitor->philos[i].ph, NULL, (void *)routine,
				&monitor->philos[i]) == 0)
			i++;
		else
			exit(EXIT_FAILURE);
	}
}
