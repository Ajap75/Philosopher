/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:10:39 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/01 18:04:37 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "function.h"

void	think(t_philo *philo)
{
		philo->status = THINKING;
		speak(philo, philo->status, START_ACTION);
		speak(philo, philo->status, END_ACTION);
}
void *routine(t_philo *philo)
{
	eat(philo);
	bedtime(philo);
	think(philo);
	// printf("Je suis le PHILO d'adresse %lu, et je parle FORT\n", philo->ph);
	return (void *)(NULL);
}
int	who_has_died(t_monitor *monitor)
{
	int i;
	int current_time;
	i = 0;
	while (i < monitor->veritas->nbr_philo)
	{
		current_time = get_time();
		if (current_time - monitor->philos[i + 1].last_meal_time >= monitor->veritas->time_to_die)
		{
			pthread_mutex_lock(&monitor->mutex.is_speaking);
			printf("%d died\n", monitor->philos[i + 1].id);
			return (1);
		}
		i++;
	}
	return (0);

}

int	is_everybody_sitting(t_monitor *monitor)
{
 	pthread_mutex_lock(&monitor->mutex.is_sitting);
	{
		if(*monitor->mutabilitas->is_sitting >= monitor->veritas->nbr_philo)
		{
			*monitor->mutabilitas->symposium_state = READY;
			return (1);
		}
		else
			return (0);
	}
}
void *routine_monitor(t_monitor *monitor)
{
	while (1)
	{
		if (is_everybody_sitting(monitor))
			break;
	}

	while(1)
	{
		if (who_has_died(monitor))
			break;

	}
	return (void *)(NULL);
}

void	eat(t_philo *philo)
{
	// pthread_mutex_lock(&philo->forks.lf);
	// pthread_mutex_lock(philo->forks.rf);
	{
		philo->last_meal_time = get_time();
		philo->status = EATING;
		philo->meals_eaten++;
		if (philo->meals_eaten >= philo->veritas->meal_target)
		{
			pthread_mutex_lock(&philo->monitor->mutex.has_eaten_enough);
			(*philo->monitor->mutabilitas->has_eaten_enough)++;
			pthread_mutex_lock(&philo->monitor->mutex.has_eaten_enough);
		}
		speak(philo, philo->status, START_ACTION);
		usleep(philo->monitor->veritas->time_to_eat * 1000);
		speak(philo, philo->status, END_ACTION);
	}
	// pthread_mutex_unlock(&philo->forks.lf);
	// pthread_mutex_unlock(philo->forks.rf);
}

void	bedtime(t_philo *philo)
{
		philo->status = SLEEPING;
		speak(philo, philo->status, START_ACTION);
		usleep(philo->monitor->veritas->time_to_sleep * 1000);
		speak(philo, philo->status, END_ACTION);
}


void	pre_drink(t_philo *philo)
{
		philo->status = APERO;
		while (1)
		{
			if(*philo->monitor->mutabilitas->symposium_state == READY)
				break;
		}
}

void	speak(t_philo *philo, int action, int statut)
{
	pthread_mutex_lock(&philo->monitor->mutex.is_speaking);
	{
		if (statut == START_ACTION)
		{
			if (action == EATING)
				printf("Philosophe number %d is eating\n", philo->id);
			else if (action == SLEEPING)
				printf("Philosophe number %d is sleeping\n", philo->id);
			else if (action == THINKING)
				printf("Philosophe number %d is thinking\n", philo->id);
		}
		else if (statut == END_ACTION)
		{
			if (action == EATING)
				printf("Philosophe number %d is done eating\n", philo->id);
			else if (action == SLEEPING)
				printf("Philosophe number %d is done sleeping\n", philo->id);
			else if (action == THINKING)
				printf("Philosophe number %d is done thinking\n", philo->id);
		}
	}
	pthread_mutex_unlock(&philo->monitor->mutex.is_speaking);
}