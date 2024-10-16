/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:10:39 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/16 14:27:10 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pre_drink(philo);
	if (philo->id % 2 == 0)
		ft_usleep(10);
	if (get_symposium_state(philo->monitor) == 1)
	{
		while (1)
		{
			if (get_symposium_state(philo->monitor) == 1
				&& get_life_statut(philo) == ALIVE)
				eat(philo);
			if (get_symposium_state(philo->monitor) == 1
				&& get_life_statut(philo) == ALIVE)
				bedtime(philo);
			if (get_symposium_state(philo->monitor) == 1
				&& get_life_statut(philo) == ALIVE)
				think(philo);
			else
				return (void *)(NULL);
		}
	}
	return (void *)(NULL);
}

void	eat(t_philo *philo)
{
	if (philo->veritas->nbr_philo > 1)
	{
		if (philo->id % 2 == 0)
			even_philo_eat(philo);
		else
			odd_philo_eat(philo);
	}
	return ;
}
void	think(t_philo *philo)
{
	philo->statut = THINKING;
	speak(philo, philo->statut);
}

void	even_philo_eat(t_philo *philo)
{
	take_left_fork_first(philo);
	{
		philo->statut = EATING;
		speak(philo, philo->statut);
		ft_usleep(philo->monitor->veritas->time_to_eat);
		set_last_meal_time(philo, get_time());
		i_finished_lunch(philo);
	}
	pthread_mutex_unlock(&philo->mutex.lf);
	pthread_mutex_unlock(philo->mutex.rf);
}

void	odd_philo_eat(t_philo *philo)
{
	{
		if (philo->meals_eaten % 2 != 0)
			ft_usleep(5);
		take_right_fork_first(philo);
		{
			philo->statut = EATING;
			speak(philo, philo->statut);
			ft_usleep(philo->monitor->veritas->time_to_eat);
			set_last_meal_time(philo, get_time());
			i_finished_lunch(philo);
		}
		pthread_mutex_unlock(philo->mutex.rf);
		pthread_mutex_unlock(&philo->mutex.lf);
	}
}

/* Depending on whether a philosopher has an odd or even ID,
they attempt to pick up either their left fork or their right fork first.
This ensures that philosophers do not all try to lock the same mutex at the
same time, reducing the risk of a deadlock.
Some philosophers will successfully pick up their first fork,
while others will have to wait until it becomes available.
Once a philosopher has successfully picked up their first fork,
they can then proceed to take the second fork,
while the others are still waiting to acquire their first.
This staggered approach helps balance the contention for
 forks and allows some philosophers to eat while others wait,
avoiding deadlock and unnecessary contention. */
