/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:10:39 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/07 15:20:49 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "structure.h"

void	think(t_philo *philo)
{
	philo->status = THINKING;
	speak(philo, philo->status, START_ACTION);
	speak(philo, philo->status, END_ACTION);
}

void	simulation_goes_on(t_monitor *monitor)
{
	if (monitor->veritas->meal_target > 0
		&& *monitor->mutabilitas->has_eaten_enough >= monitor->veritas->meal_target)
		set_symposium_state(monitor, -1);
	else if (*monitor->mutabilitas->dead_ph_id != -1)
		set_symposium_state(monitor, -1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (pthread_mutex_lock(&philo->monitor->mutex.is_speaking) == 0)
		{
			printf("Philo num %d rentre dans sa routine \n", philo->id);
			pthread_mutex_unlock(&philo->monitor->mutex.is_speaking);
			break ;
		}
	}
	pre_drink(philo);
	while (get_symposium_state(philo->monitor) == 1)
	{
		eat(philo);
		bedtime(philo);
		think(philo);
	}
	// printf("Je suis le PHILO d'adresse %lu, et je parle FORT\n", philo->ph);
	return (void *)(NULL);
}
int	who_has_died(t_monitor *monitor)
{
	int	i;
	long long	current_time;
	long long	last_meal_time;

	i = 0;
	while (i < monitor->veritas->nbr_philo)
	{
		current_time = get_time();
		last_meal_time = get_last_meal_time(&monitor->philos[i]);
		if (current_time - last_meal_time >= monitor->veritas->time_to_die)
		{
			pthread_mutex_lock(&monitor->mutex.is_speaking);
			printf("Last meal time = %lld\n", get_last_meal_time(&monitor->philos[i]));
			printf("current time = %lld\n", current_time);
			printf("Delta = %lld\n", current_time - get_last_meal_time(&monitor->philos[i]));
			printf("meals eaten = %d\n", get_meals_eaten(&monitor->philos[i]));
			printf("%d died\n", monitor->philos[i].id);
			pthread_mutex_unlock(&monitor->mutex.is_speaking);
			set_symposium_state(monitor, -1);
		}
		i++;
	}
	return (0);
}

void	smbd_has_eaten_enough(t_monitor *monitor)
{
	if (monitor->veritas->meal_target > 0
		&& *monitor->mutabilitas->has_eaten_enough >= monitor->veritas->meal_target)
		set_symposium_state(monitor, -1);
}

int		is_everybody_sitting(t_monitor *monitor)
{
		if (get_is_sitting(monitor) == monitor->veritas->nbr_philo)
		{
			set_symposium_state(monitor, 1);
			return (1);
		}
		return(0);
}
void	*routine_monitor(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	while (1)
	{
		if (is_everybody_sitting(monitor) == 1)
			break;
	}
	while (get_symposium_state(monitor) == 1)
	{
		who_has_died(monitor);
		smbd_has_eaten_enough(monitor);
	}
	return (void *)(NULL);
}

void	eat(t_philo *philo)
{
	// pthread_mutex_lock(&philo->forks.lf);
	// pthread_mutex_lock(philo->forks.rf);
	{
		set_last_meal_time(philo, get_time());
		philo->status = EATING;
		i_finished_lunch(philo);
		if (philo->veritas->meal_target >= 0
			&& philo->meals_eaten >= philo->veritas->meal_target)
		{
			pthread_mutex_lock(&philo->monitor->mutex.has_eaten_enough);
			(*philo->monitor->mutabilitas->has_eaten_enough)++;
			pthread_mutex_lock(&philo->monitor->mutex.has_eaten_enough);
		}
		speak(philo, philo->status, START_ACTION);
		usleep(philo->monitor->veritas->time_to_eat);
		speak(philo, philo->status, END_ACTION);
	}
	// pthread_mutex_unlock(&philo->forks.lf);
	// pthread_mutex_unlock(philo->forks.rf);
}
void	pre_drink(t_philo *philo)
{
	philo->status = APERO;
	i_am_sitting(philo->monitor);
	while (1)
	{
		if (get_symposium_state(philo->monitor) == 1)
		{
			pthread_mutex_lock(&philo->monitor->mutex.is_speaking);
			printf("get_symposium_state(philo->monitor) = %d\n", get_symposium_state(philo->monitor));
			pthread_mutex_unlock(&philo->monitor->mutex.is_speaking);

			break ;
		}
	}
}

void	bedtime(t_philo *philo)
{
	philo->status = SLEEPING;
	speak(philo, philo->status, START_ACTION);
	usleep(philo->monitor->veritas->time_to_sleep);
	speak(philo, philo->status, END_ACTION);
}

void	speak(t_philo *philo, int action, int statut)
{
	while (1)
	{
		if (pthread_mutex_lock(&philo->monitor->mutex.is_speaking) == 0)
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
					printf("Philosophe number %d is done sleeping\n",
						philo->id);
				else if (action == THINKING)
					printf("Philosophe number %d is done thinking\n",
						philo->id);
			}
		pthread_mutex_unlock(&philo->monitor->mutex.is_speaking);
			break ;
		}
	}
}