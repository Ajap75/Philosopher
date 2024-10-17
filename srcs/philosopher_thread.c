/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:10:39 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/17 18:05:39 by anastruc         ###   ########.fr       */
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
		ft_usleep(5);
	if (get_symposium_state(philo->monitor) == 1)
	{
		while (get_symposium_state(philo->monitor) == 1)
		{
			if (get_symposium_state(philo->monitor) == 1)
				eat(philo);
			if (get_symposium_state(philo->monitor) == 1)
				bedtime(philo);
			if (get_symposium_state(philo->monitor) == 1)
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
	int	is_odd;

	philo->statut = THINKING;
	speak(philo, philo->statut);
	// if (philo->monitor->veritas->time_to_eat > philo->monitor->veritas->time_to_sleep)
	// 	ft_usleep(philo->monitor->veritas->time_to_eat - philo->monitor->veritas->time_to_sleep);
	if (philo->id % 2 != 0)
		is_odd = 5;
	else
		is_odd = 0;
	if (philo->monitor->veritas->nbr_philo % 2 != 0
		&& philo->monitor->veritas->time_to_eat >= philo->monitor->veritas->time_to_sleep)
		ft_usleep(is_odd + (philo->monitor->veritas->time_to_eat
				- philo->monitor->veritas->time_to_sleep));
}

void	even_philo_eat(t_philo *philo)
{
	take_left_fork_first(philo);
	{
		if (philo->meals_eaten % 2 == 0)
			ft_usleep(5);
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

/*I implemented three stage of synchronisation to avoid the death of a philosopher.

1) The odd philos jump in the simulation (eat, sleep, thing) loop, with a delay of 10ms. Solve the problem in classics simulation condition (even number of philos)

2) Every odd philosopher delay their eat action by 5ms in one meal of two. I think we can even simplify applying this delay only to the last or the first philosopher.

3) When the sleep time is lower than the eat time and it's an odd number of philos simulation. Those begining to eat the first meal and those having the second meal, will be already in line for the third meal and lock the mutex blocking the looser of the two first meal to eat. */
