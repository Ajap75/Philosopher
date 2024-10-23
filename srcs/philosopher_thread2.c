/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:24:06 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/23 12:17:00 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

void	even_philo_eat(t_philo *philo)
{
	take_left_fork_first(philo);
	philo->statut = EATING;
	speak(philo, philo->statut);
	set_last_meal_time(philo, get_time());
	if (philo->veritas->time_to_die < philo->veritas->time_to_eat)
	{
		ft_usleep(philo->veritas->time_to_die);
	}
	else
		ft_usleep(philo->monitor->veritas->time_to_eat);
	i_finished_lunch(philo);
	pthread_mutex_unlock(&philo->mutex.lf);
	pthread_mutex_unlock(philo->mutex.rf);
}

void	odd_philo_eat(t_philo *philo)
{
	if (philo->meals_eaten % 2 != 0)
		ft_usleep(2);
	take_right_fork_first(philo);
	{
		philo->statut = EATING;
		speak(philo, philo->statut);
		set_last_meal_time(philo, get_time());
		if (philo->veritas->time_to_die < philo->veritas->time_to_eat)
		{
			ft_usleep(philo->veritas->time_to_die);
		}
		else
			ft_usleep(philo->monitor->veritas->time_to_eat);
		i_finished_lunch(philo);
	}
	pthread_mutex_unlock(philo->mutex.rf);
	pthread_mutex_unlock(&philo->mutex.lf);
}

void	speak(t_philo *philo, int action)
{
	if (action == EATING)
		secure_print("is eating", philo, YELLOW);
	else if (action == SLEEPING)
		secure_print("is sleeping", philo, BLUE);
	else if (action == THINKING)
		secure_print("is thinking", philo, GREEN);
	else if (action == HAS_TAKEN_A_FORK)
		secure_print("has taken a fork", philo, PURPLE);
	else if (action == DEAD)
		secure_print_death("died", philo, RED);
}

void	secure_print(char *s, t_philo *philo, char *color)
{
	unsigned long	time;

	if (am_i_dead(philo))
		return ;
	pthread_mutex_lock(&philo->monitor->mutex.speak);
	time = get_time() - philo->monitor->veritas->start_time;
	printf("%s%ld %d %s%s\n", color, time, philo->id, s, RESET);
	pthread_mutex_unlock(&philo->monitor->mutex.speak);
}

void	secure_print_death(char *s, t_philo *philo, char *color)
{
	unsigned long	time;

	ft_usleep(3);
	time = get_time() - philo->monitor->veritas->start_time;
	pthread_mutex_lock(&philo->monitor->mutex.speak);
	printf("%s%ld %d %s%s\n", color, time, philo->id, s, RESET);
	pthread_mutex_unlock(&philo->monitor->mutex.speak);
	*philo->monitor->mutabilitas->stop_flag = 1;
}
