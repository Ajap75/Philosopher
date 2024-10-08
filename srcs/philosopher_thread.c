/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:10:39 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/08 16:09:29 by anastruc         ###   ########.fr       */
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
	while (get_symposium_state(philo->monitor) == 1)
	{
		eat(philo);
		bedtime(philo);
		think(philo);
		if (pthread_mutex_lock(&philo->monitor->mutex.is_speaking) == 0)
		{
			printf("Philo num %d fin de routine\n", philo->id);
			pthread_mutex_unlock(&philo->monitor->mutex.is_speaking);
		}
		break ;
	}
	return (void *)(NULL);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks.lf);
	pthread_mutex_lock(philo->forks.rf);
	{
		set_last_meal_time(philo, get_time());
		philo->status = EATING;
		i_finished_lunch(philo);
		speak(philo, philo->status);
		ft_usleep(philo->monitor->veritas->time_to_eat);
	}
	pthread_mutex_unlock(&philo->forks.lf);
	pthread_mutex_unlock(philo->forks.rf);
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
				printf("%zu %d \033[0;33mis eating\033[0m\n", get_time(),
					philo->id);
			else if (action == SLEEPING)
				printf("%zu %d \033[0;32mis sleeping\033[0m\n", get_time(),
					philo->id);
			else if (action == THINKING)
				printf("%zu %d \033[0;34mis thinking\033[0m\n", get_time(),
					philo->id);
			pthread_mutex_unlock(&philo->monitor->mutex.is_speaking);
			break ;
		}
	}
}
