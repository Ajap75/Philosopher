/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:10:39 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/22 17:59:17 by anastruc         ###   ########.fr       */
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
	while (am_i_dead(philo) == 0)
	{
		if (am_i_dead(philo) == 0)
			eat(philo);
		if (am_i_dead(philo) == 0
			&& (philo->veritas->time_to_die > philo->veritas->time_to_eat))
			bedtime(philo);
		if (am_i_dead(philo) == 0
			&& (philo->veritas->time_to_die > (philo->veritas->time_to_eat
					+ philo->veritas->time_to_sleep)))
			think(philo);
	}
	return ((void *)(NULL));
}

void	pre_drink(t_philo *philo)
{
	while (get_time() < philo->veritas->start_time)
	{
		ft_usleep(1);
	}
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

void	bedtime(t_philo *philo)
{
	philo->statut = SLEEPING;
	speak(philo, philo->statut);
	if (philo->veritas->time_to_die < philo->veritas->time_to_sleep)
	{
		ft_usleep(philo->veritas->time_to_die);
	}
	else
		ft_usleep(philo->monitor->veritas->time_to_sleep);
}

void	think(t_philo *philo)
{
	int	is_odd;

	philo->statut = THINKING;
	speak(philo, philo->statut);
	if (philo->id % 2 != 0)
		is_odd = 5;
	else
		is_odd = 0;
	if (philo->monitor->veritas->nbr_philo % 2 != 0
		&& philo->monitor->veritas->time_to_eat > philo->monitor->veritas->time_to_sleep)
		ft_usleep(is_odd + (philo->monitor->veritas->time_to_eat
				- philo->monitor->veritas->time_to_sleep));
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

/*
First Stage of Synchronization:

Odd-numbered philosophers start the simulation loop (eat, sleep,
	think) with a
delay of 10ms. This initial stagger prevents immediate contention over shared
resources (forks) and resolves issues under classic simulation conditions,
especially when the number of philosophers is even.

Second Stage of Synchronization:

Every odd-numbered philosopher delays their eating action by 5ms on every second
meal (i.e., one meal out of two). This additional delay helps to further
distribute resource access and can be simplified by applying it only to the
first or last philosopher.

Third Stage of Synchronization:

When the simulation involves an odd number of philosophers and the time to sleep
is shorter than or equal to the time to eat, a synchronization mechanism is
needed to prevent certain philosophers from monopolizing the forks.

Without intervention, philosophers who start eating first can continually
acquire the forks ahead of others,
	leading to starvation of some philosophers.

To counter this,
	we introduce a calculated delay during the thinking phase for
odd-numbered philosophers. This delay aligns the timing of philosophers
attempting to eat,
	ensuring that all have a fair chance to acquire the forks.

By strategically delaying certain philosophers,
	we prevent resource conflicts
and promote equitable access,
	thereby avoiding deadlocks and ensuring the smooth
progression of the simulation.
*/