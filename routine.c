/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:10:39 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/08 12:48:31 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "structure.h"

void	think(t_philo *philo)
{
	philo->status = THINKING;
	speak(philo, philo->status, START_ACTION);
	// speak(philo, philo->status, END_ACTION);
}

void	simulation_goes_on(t_monitor *monitor)
{
	if (monitor->veritas->meal_target > 0
		&& *monitor->mutabilitas->has_eaten_enough >= monitor->veritas->meal_target)
		set_symposium_state(monitor, -1);
	else if (*monitor->mutabilitas->dead_ph_id != -1)
		set_symposium_state(monitor, -1);
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
	}
	// printf("Je suis le PHILO d'adresse %lu, et je parle FORT\n", philo->ph);
	return (void *)(NULL);
}
int	who_has_died(t_monitor *monitor)
{
	int	i;
	long long	current_time;
	long long	last_meal_time;

	i = 0;
	while (i < monitor->veritas->nbr_philo)
	{
		current_time = get_time();
		last_meal_time = get_last_meal_time(&monitor->philos[i]);
		if (current_time - last_meal_time >= monitor->veritas->time_to_die)
		{
			pthread_mutex_lock(&monitor->mutex.is_speaking);
			printf("Time to die = %d\n", monitor->veritas->time_to_die);
			printf("Last meal time = %lld\n", get_last_meal_time(&monitor->philos[i]));
			printf("current time = %lld\n", current_time);
			printf("Delta = %lld\n", current_time - get_last_meal_time(&monitor->philos[i]));
			printf("meals eaten = %d\n", get_meals_eaten(&monitor->philos[i]));
			printf("%d died\n", monitor->philos[i].id);
			pthread_mutex_unlock(&monitor->mutex.is_speaking);
			set_symposium_state(monitor, -1);
		}
		i++;
	}
	return (0);
}


int		is_everybody_sitting(t_monitor *monitor)
{
		if (get_is_sitting(monitor) == monitor->veritas->nbr_philo)
		{
			monitor->veritas->start_time = get_time();
			set_symposium_state(monitor, 1);
			return (1);
		}
		return(0);
}
void	*routine_monitor(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	while (1)
	{
		if (is_everybody_sitting(monitor) == 1)
			break;
	}
	while (get_symposium_state(monitor) == 1)
	{
		if (monitor->veritas->meal_target != -1)
		{
			who_has_eaten_enough(monitor);
		}
		who_has_died(monitor);
	}
	return (void *)(NULL);
}
void	who_has_eaten_enough(t_monitor *monitor)
{
	int i;
	int j;
	i = 0;
	j = 0;
	if (get_fed_philos_count(monitor) == monitor->veritas->nbr_philo)
		{
			pthread_mutex_lock(&monitor->mutex.is_speaking);
			printf("EVERY PHILOSOPHER HAS EATEN ENOUGH\n");
			pthread_mutex_unlock(&monitor->mutex.is_speaking);
			set_symposium_state(monitor, -1);
			return ;
			// free and exit
		}
	while (i < monitor->veritas->nbr_philo)
	{
		if (get_meals_eaten(&monitor->philos[i]) >= monitor->veritas->meal_target)
		{
			j++;
			pthread_mutex_lock(&monitor->mutex.is_speaking);
			printf("UN PHILO A MANGER TOUT SES REPAS\n");
			pthread_mutex_unlock(&monitor->mutex.is_speaking);

		}
		i++;
	}
	update_fed_philos_count(monitor, j);
}
		// if (philo->veritas->meal_target != 0
		// 	&& philo->meals_eaten >= philo->veritas->meal_target)
		// {
		// 	pthread_mutex_lock(&philo->monitor->mutex.has_eaten_enough);
		// 	(*philo->monitor->mutabilitas->has_eaten_enough)++;
		// 	pthread_mutex_unlock(&philo->monitor->mutex.has_eaten_enough);
		// }
void	eat(t_philo *philo)
{
	// pthread_mutex_lock(&philo->forks.lf);
	// pthread_mutex_lock(philo->forks.rf);
	{
		set_last_meal_time(philo, get_time());
		philo->status = EATING;
		i_finished_lunch(philo);
		speak(philo, philo->status, START_ACTION);
		ft_usleep(philo->monitor->veritas->time_to_eat);
		// speak(philo, philo->status, END_ACTION);
	}
	// pthread_mutex_unlock(&philo->forks.lf);
	// pthread_mutex_unlock(philo->forks.rf);
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
			printf("get_symposium_state(philo->monitor) = %d\n", get_symposium_state(philo->monitor));
			pthread_mutex_unlock(&philo->monitor->mutex.is_speaking);

			break ;
		}
	}
}

void	bedtime(t_philo *philo)
{
	philo->status = SLEEPING;
	speak(philo, philo->status, START_ACTION);
	ft_usleep(philo->monitor->veritas->time_to_sleep);
	// speak(philo, philo->status, END_ACTION);
}

void	speak(t_philo *philo, int action, int statut)
{
	while (1)
	{
		if (pthread_mutex_lock(&philo->monitor->mutex.is_speaking) == 0)
		{
			if (statut == START_ACTION)
			{
				if (action == EATING)
					printf("%zu %d \033[0;33mis eating\033[0m\n",get_time(), philo->id);
				else if (action == SLEEPING)
					printf("%zu %d \033[0;32mis sleeping\033[0m\n", get_time(), philo->id);
				else if (action == THINKING)
					printf("%zu %d \033[0;34mis thinking\033[0m\n", get_time(), philo->id);
			}
			else if (statut == END_ACTION)
			{
				if (action == EATING)
					printf("%zu %d \033[0;33mis done eating\033[0m\n", get_time(), philo->id);
				else if (action == SLEEPING)
					printf("%zu %d \033[0;32mis done sleeping\033[0m\n", get_time(),
						philo->id);
				else if (action == THINKING)
					printf("%zu %d \033[0;34mis done thinking\033[0m\n", get_time(),
						philo->id);
			}
		pthread_mutex_unlock(&philo->monitor->mutex.is_speaking);
			break ;
		}
	}
}

// ("\n \033[0;33m*** Monitor informtions ***\033[0m\n")