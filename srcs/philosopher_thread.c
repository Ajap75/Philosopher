/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:10:39 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/10 17:38:15 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

void	think(t_philo *philo)
{
	philo->status = THINKING;
	speak(philo, philo->status);
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
	if (philo->id % 2 == 0)
		ft_usleep(5);
	if (get_symposium_state(philo->monitor) == 1)
	{
		while (1)
		{
			// printf("Philo  %d STATUT = %d  \n", philo->id, philo->status);
			if (get_symposium_state(philo->monitor) == 1 && get_life_statut(philo) == ALIVE)
				eat(philo);
			if (get_symposium_state(philo->monitor) == 1 && get_life_statut(philo) == ALIVE)
				bedtime(philo);
			if (get_symposium_state(philo->monitor) == 1 && get_life_statut(philo) == ALIVE)
				think(philo);
			else
				return (void *)(NULL);
		}
	}
	return (void *)(NULL);
}

int am_i_alive(t_philo *philo)
{
	int rtn;
	pthread_mutex_lock(&philo->mutex.life);
	if (philo->life == ALIVE)
		rtn = 1;
	else
		rtn = 0;
	pthread_mutex_unlock(&philo->mutex.life);
	return(rtn);
}

// void	i_tell_monitor_i_am_dead (t_philo)
// {

// }


void	even_philo_eat(t_philo *philo)
{
	take_left_fork_first(philo);
	{
		philo->status = EATING;
		speak(philo, philo->status);
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
		take_right_fork_first(philo);
		{
			philo->status = EATING;
			speak(philo, philo->status);
			ft_usleep(philo->monitor->veritas->time_to_eat);
			set_last_meal_time(philo, get_time());
			i_finished_lunch(philo);
		}
		pthread_mutex_unlock(philo->mutex.rf);
		pthread_mutex_unlock(&philo->mutex.lf);
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

// Depending on whether a philosopher has an odd or even ID, they attempt to pick up either their left fork or their right fork first.
// This ensures that philosophers do not all try to lock the same mutex at the same time, reducing the risk of a deadlock.
// Some philosophers will successfully pick up their first fork, while others will have to wait until it becomes available.
// Once a philosopher has successfully picked up their first fork, they can then proceed to take the second fork, while the others are still waiting to acquire their first.
// This staggered approach helps balance the contention for forks and allows some philosophers to eat while others wait, avoiding deadlock and unnecessary contention.
}
void	pre_drink(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex.life);
	philo->life = ALIVE;
	pthread_mutex_unlock(&philo->mutex.life);

	i_am_sitting(philo->monitor);
	while (1)
	{
		if (get_symposium_state(philo->monitor) == 1)
		{
			pthread_mutex_lock(&philo->monitor->mutex.is_speaking);
			printf("get_symposium_state(philo->monitor) = %d\n",
				get_symposium_state(philo->monitor));
			pthread_mutex_unlock(&philo->monitor->mutex.is_speaking);
			break ;
		}
	}
}

void	bedtime(t_philo *philo)
{
	philo->status = SLEEPING;
	speak(philo, philo->status);
	ft_usleep(philo->monitor->veritas->time_to_sleep);
}

void	speak(t_philo *philo, int action)
{
	while (1)
	{

		if (pthread_mutex_lock(&philo->monitor->mutex.is_speaking) == 0)
		{
			if (action == EATING)
				printf("%zu %d \033[0;33mis eating\033[0m\n", get_time() - philo->veritas->start_time,
					philo->id);
			else if (action == SLEEPING)
				printf("%zu %d \033[0;32mis sleeping\033[0m\n", get_time() - philo->veritas->start_time,
					philo->id);
			else if (action == THINKING)
				printf("%zu %d \033[0;34mis thinking\033[0m\n", get_time() - philo->veritas->start_time,
					philo->id);
			else if (action == HAS_TAKEN_A_FORK)
				printf("%zu %d \033[0;35mhas taken a fork\033[0m\n", get_time() - philo->veritas->start_time,
					philo->id);
			pthread_mutex_unlock(&philo->monitor->mutex.is_speaking);
			break ;
		}
	}
}
