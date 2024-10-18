/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:24:06 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/18 15:21:17 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

void	pre_drink(t_philo *philo)
{
	// pthread_mutex_lock(&philo->mutex.life);
	// philo->life = ALIVE;
	// pthread_mutex_unlock(&philo->mutex.life);
	i_am_sitting(philo->monitor);
	while (1)
	{
		if (get_symposium_state(philo->monitor) == 1)
			break ;
	}
}

void	bedtime(t_philo *philo)
{
	philo->statut = SLEEPING;
	speak(philo, philo->statut);
	ft_usleep(philo->monitor->veritas->time_to_sleep);
}

void	speak(t_philo *philo, int action)
{
	if (get_symposium_state(philo->monitor) == 1)
	{
		if (action == EATING)
			secure_print("is eating", philo, YELLOW, 0);
		else if (action == SLEEPING)
			secure_print("is sleeping", philo, BLUE, 0);
		else if (action == THINKING)
			secure_print("is thinking", philo, GREEN, 0);
		else if (action == HAS_TAKEN_A_FORK)
			secure_print("has taken a fork", philo, PURPLE, 0);
		else if (action == DEAD)
			secure_print("died", philo, RED, 1);
	}
}

void	secure_print(char *s, t_philo *philo, char *color, int end_flag)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->monitor->mutex.symposium_state);
	if (*philo->monitor->mutabilitas->symposium_state == -1)
	{
		pthread_mutex_unlock(&philo->monitor->mutex.symposium_state);
		return ;
	}
	time = get_time() - philo->monitor->veritas->start_time;
	printf("%s%ld %d %s%s\n", color, time, philo->id, s, RESET);
	if (end_flag == 1)
		*philo->monitor->mutabilitas->symposium_state = -1;
	pthread_mutex_unlock(&philo->monitor->mutex.symposium_state);
}
