/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:10:39 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/16 12:25:23 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

void	think(t_philo *philo)
{
	philo->statut = THINKING;
	speak(philo, philo->statut);
}

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
	// // Depending on whether a philosopher has an odd or even ID,
	// 	they attempt to pick up either their left fork or their right fork first.
	// // This ensures that philosophers do not all try to lock the same mutex at the same time,
	// 	reducing the risk of a deadlock.
	// // Some philosophers will successfully pick up their first fork,
	// 	while others will have to wait until it becomes available.
	// // Once a philosopher has successfully picked up their first fork,
	// 	they can then proceed to take the second fork,
	// 	while the others are still waiting to acquire their first.
	// // This staggered approach helps balance the contention for forks and allows some philosophers to eat while others wait,
		// avoiding deadlock and unnecessary contention.
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
	philo->statut = SLEEPING;
	speak(philo, philo->statut);
	ft_usleep(philo->monitor->veritas->time_to_sleep);
}

// void	speak(t_philo *philo, int action)
// {
// 	if (get_symposium_state(philo->monitor) == 1)
// 	{
// 		while (1)
// 		{
// 			if (pthread_mutex_lock(&philo->monitor->mutex.is_speaking) == 0)
// 			{
// 				if (action == EATING)
// 					printf("%zu %d \033[0;33mis eating DELTA = %zu\033[0m\n",
// 						get_time() - philo->veritas->start_time, philo->id,
// 						get_time() - philo->last_meal_time);
// 				else if (action == SLEEPING)
// 					printf("%zu %d \033[0;32mis sleeping\033[0m\n", get_time()
// 						- philo->veritas->start_time, philo->id);
// 				else if (action == THINKING)
// 					printf("%zu %d \033[0;34mis thinking\033[0m\n", get_time()
// 						- philo->veritas->start_time, philo->id);
// 				else if (action == HAS_TAKEN_A_FORK)
// 					printf("%zu %d \033[0;35mhas taken a fork\033[0m\n",
// 						get_time() - philo->veritas->start_time, philo->id);
// 				pthread_mutex_unlock(&philo->monitor->mutex.is_speaking);
// 				break ;
// 			}
// 		}
// 	}
// }

void	speak(t_philo *philo, int action)
{
		if (action == EATING)
			secure_print("is eating\n", philo, YELLOW, get_time());
		else if (action == SLEEPING)
			secure_print("is thinking\n", philo, BLUE, get_time());
		else if (action == THINKING)
			secure_print("is sleeping\n", philo, GREEN, get_time());
		else if (action == HAS_TAKEN_A_FORK)
			secure_print("has taken a fork\n", philo, PURPLE, get_time());
		else if (action == DEAD)
			secure_print("died\n", philo, RED, get_time());

}

void	secure_print(char *s, t_philo *philo, char *color,
		unsigned long time_in_ms)
{
	unsigned long	time;

	time = time_in_ms - philo->monitor->veritas->start_time;
	if (get_symposium_state(philo->monitor) != 1)
		return ;
	pthread_mutex_lock(&philo->monitor->mutex.is_speaking);
	printf("%s%ld %d %s%s\n", color, time, philo->id, s, RESET);
	pthread_mutex_unlock(&philo->monitor->mutex.is_speaking);
}