/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:10:39 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/02 16:25:52 by anastruc         ###   ########.fr       */
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

int	simulation_goes_on(t_monitor *monitor)
{
	if (monitor->veritas->meal_target > 0
		&& *monitor->mutabilitas->has_eaten_enough >= monitor->veritas->meal_target)
		return (0);
	else if (*monitor->mutabilitas->dead_ph_id != -1)
		return (0);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_is_speaking(philo->monitor) == 0)
		{
			set_is_speaking(philo->monitor, 1);
			printf("Philo num %d rentre dans sa routine \n", philo->id);
			set_is_speaking(philo->monitor, 0);
			break ;
		}
	}
	while (simulation_goes_on(philo->monitor))
	{
		pre_drink(philo);
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
	int	current_time;

	i = 0;
	while (i < monitor->veritas->nbr_philo)
	{
		current_time = get_time();
		if (current_time - monitor->philos[i
			+ 1].last_meal_time >= monitor->veritas->time_to_die)
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
	{
		if (get_is_sitting(monitor) == monitor->veritas->nbr_philo)
		{
			set_is_sitting(monitor, READY);
			return (1);
		}
		else
			return (0);
	}
}
void	*routine_monitor(void *arg)
{
	t_monitor	*monitor;
	int			result;

	monitor = (t_monitor *)arg;
	while (1)
	{
		result = is_everybody_sitting(monitor);
		if (result == 1)
		{
			printf("result = %d\n", result);
			break ;
		}
	}
	while (1)
	{
		if (who_has_died(monitor))
			break ;
		printf("1\n");
	}
	printf("3\n");
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
		if (philo->veritas->meal_target >= 0
			&& philo->meals_eaten >= philo->veritas->meal_target)
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
void	pre_drink(t_philo *philo)
{
	philo->status = APERO;
	while (1)
	{
		if (get_symposium_state(philo->monitor) == READY)
			break ;
	}
}

void	bedtime(t_philo *philo)
{
	philo->status = SLEEPING;
	speak(philo, philo->status, START_ACTION);
	usleep(philo->monitor->veritas->time_to_sleep * 1000);
	speak(philo, philo->status, END_ACTION);
}

void	speak(t_philo *philo, int action, int statut)
{
	while (1)
	{
		if (get_is_speaking(philo->monitor) == 0)
		{
			set_is_speaking(philo->monitor, 1);
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
			set_is_speaking(philo->monitor, 0);
			break ;
		}
	}
}