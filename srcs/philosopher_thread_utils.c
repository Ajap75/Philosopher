/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:24:06 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/16 16:16:30 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

void	pre_drink(t_philo *philo)
{

	pthread_mutex_lock(&philo->mutex.life);
	philo->life = ALIVE;
	pthread_mutex_unlock(&philo->mutex.life);
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
		if (action == EATING)
			secure_print("is eating\n", philo, YELLOW, get_time());
		else if (action == SLEEPING)
			secure_print("is sleeping\n", philo, BLUE, get_time());
		else if (action == THINKING)
			secure_print("is thinking\n", philo, GREEN, get_time());
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

