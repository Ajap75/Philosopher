/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:12:48 by anastruc          #+#    #+#             */
/*   Updated: 2024/09/30 19:44:33 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "function.h"

// void	*speak(void *){printf("HELLO WORLD FROM THREAD NUMBER %d\n,")}

// init_ph_struc(int nbr_philo)
// {
// 	int	i;

// 	pthread_t[nbr_philo];
// 	i = 0;
// 	while (i < nbr_philo)
// 	{
// 	}
// 	while (i < nbr_philo)
// 	{
// 		pthread_create(&pi, NULL, &speak, void *(nbr));
// 		pi++;
// 	}
// 	i = 0;
// 	while (i < nbr_philo)
// 	{
// 		pthread_join(&pi, NULL, &speak, void *());
// 		pi++;
// 	}
// }


// 4 ou 5 argument
// Le programme prendra 5 arguments en parametre :
// Number of philosopher : The number of philosopher and also the numer of forks
// Time to die : If a philosopher didn’t start to eat time to die (milliseconde  since his last meal or since the beginning of the simulation, they die)
// Time to eat : The time a philosopher need to eat, during that time he will need to hold two forks.
// Time to sleep : The time a philosopher will spend sleeping
// Number of time each philosopher must eat. Optional, if not specified, the simulation stop when one philosopher die



int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int is_arg_digit(int argc, char **argv)
{
	int i;
	int j;
	j = 0;
	i = 1;
	while (i < argc)
	{
	printf("ARG num %d = %s\n", i, argv[i]);
		while(argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				write(1, "Arguments must be digits", 25);
				return(1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return(0);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	result;
	int	digit;

	sign = 1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	digit = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		digit = *nptr - 48;
		result = result * 10 + digit;
		nptr++;
	}
	return (sign * result);
}
int	parsing(int argc, char **argv, t_monitor *monitor)
{
	(void)monitor;
	if (argc >= 5 && argc <= 6)
	{
		if (is_arg_digit(argc, argv))
			return(1);
		// if(is_arg_an_positive_int(argc, argv))

		// set_nbr_philo(monitor, argv[1]);
		if (ft_atoi(argv[1]) < 1)
		{
			write(1, "Not enough philosopher to run the simulation\n", 46);
			return(1);
		}
	}
	else
	{
		write (1, "Missing arguments", 18);
		return(1);
	}
	return(0);
}
int	get_time()
{
	struct timeval current_time ;
	gettimeofday(&current_time, NULL);
	return (current_time.tv_usec);
}

void init_monitor(t_monitor *monitor, int argc, char *argv[])
{
	monitor->veritas = malloc(sizeof(t_veritas));
	monitor->veritas->nbr_philo = ft_atoi(argv[1]);
	monitor->veritas->time_to_die = ft_atoi(argv[2]);
	monitor->veritas->time_to_eat = ft_atoi(argv[3]);
	monitor->veritas->time_to_sleep = ft_atoi(argv[4]);
	monitor->veritas->start_time = get_time();

	if (argc == 6)
		monitor->veritas->meal_target = ft_atoi(argv[5]);
	else
		monitor->veritas->meal_target = -1;
	monitor->philos = malloc(sizeof(t_philo) * monitor->veritas->nbr_philo);
	return ;
}

void	speak(t_philo *philo)
{
	pthread_mutex_lock(philo->monitor->mutex.is_speaking);
	{
		printf("Philosophe number %d is eating\n", philo->id);
	}
	pthread_mutex_unlock(philo->monitor->mutex.is_speaking);


}
void	eat(t_philo *philo)
{
	printf("Je passe la routine\n");
	pthread_mutex_lock(philo->forks.lf.lf);
	pthread_mutex_lock(&philo->forks.rf.rf);
	{
		philo->meals_eaten++;
		speak(philo);
		usleep(philo->monitor->veritas->time_to_eat * 1000);
		printf("Philosophe number %d is done eating\n", philo->id);

	}
	pthread_mutex_unlock(philo->forks.lf.lf);
	pthread_mutex_unlock(&philo->forks.rf.rf);
}
int	init_fork(t_monitor *monitor, t_philo *philo)
{
		pthread_mutex_init(&philo->forks.lf, NULL);

		if (philo->id == monitor->veritas->nbr_philo)
			philo->forks.rf = philo[0].forks.lf;
		else
			philo->forks.rf = philo[philo->id + 1].forks->lf;

	return(0);
}
void *routine(t_philo *philo)
{
	printf("Je passe la routine\n");
	eat(philo);
	// sleep(monitor);
	// think(monitor);
	// printf("Je suis le PHILO d'adresse %lu, et je parle FORT\n", philo->ph);
	return (void *)(NULL);
}

void	init_philos(t_monitor *monitor)
{
	printf("Je passe la\n");
	int i;

	i = 0;
	while(i < monitor->veritas->nbr_philo)
	{
		monitor->philos[i].id = i + 1;
		monitor->philos[i].meals_eaten = 0;
		monitor->philos[i].time_since_lase_meal = 0;
		monitor->philos[i].status = 0;
		monitor->philos[i].meals_eaten = 0;
		monitor->philos[i].veritas= monitor->veritas;
		monitor->philos[i].monitor= monitor;
		init_fork(monitor, &monitor->philos[i]);
		pthread_create(&monitor->philos[i].ph, NULL, (void *)routine, &monitor->philos[i]);
		i++;
	}
	i = 0;

	while(i < monitor->veritas->nbr_philo)
	{
		pthread_join(monitor->philos[i].ph, NULL);
		i++;
	}

}

// void	destroy_philos(t_monitor *monitor)
// {
// 	int i;
// 	i = 0;

// 	while (*(monitor->philos[i])
// 	{
// 		free(monitor->philos)
// 	}
// }

int	main(int argc, char *argv[])
{
	t_monitor monitor;
	int i;

	i = 0;

	if ((parsing(argc, argv, &monitor)))
		return(1);
	init_monitor(&monitor, argc, argv);

	init_philos(&monitor);
	// init_fork(&monitor);
	// destroy_philos(&monitor);
	// int nbr_philo;z		monitor->philos[i].forks.rf.rf = &monitor->philos[i + 1].forks.lf.lf;

	// nbr_philo = atoi(argv[1]);
	// if (argc >= 2)
	// {
	// 	init_ph(nbr_philo);

	printf("\n \033[0;33m*** SIMULATION CONDITIONS ***\033[0m\n");
	printf("  Number of philosopher = %d\n", monitor.veritas->nbr_philo);
	printf("  Time to die = %d\n", monitor.veritas->time_to_die);
	printf("  Time to eat = %d\n", monitor.veritas->time_to_eat);
	printf("  Time to sleep = %d\n", monitor.veritas->time_to_sleep);
	printf("  Meal goal = %d\n\n", monitor.veritas->meal_target);
	printf("  Start Time = %d\n\n", monitor.veritas->start_time);


	// printf("\n \033[0;33m*** FORK STATE ***\033[0m\n");
	// while (i < monitor.veritas->nbr_philo)
	// {
	// 	printf(" Philo name :%d, left fork = %d and right fork = %d\n", monitor.philos[i].id, monitor.philos[i].forks.lf.id, *monitor.philos[i].forks.rf.id);
	// 	i++;
	// }


	write(1, "PARSING OK\n", 12);
	clean(&monitor);
	return(0);
}
