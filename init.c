/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:12:48 by anastruc          #+#    #+#             */
/*   Updated: 2024/09/25 17:19:53 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

int	parsing(int argc, char **argv, t_data_sim *big_brother)
{
	if (argc >= 5 && argc <= 6)
	{
		if (is_arg_digit(argc, argv))
			return(1);
		// if(is_arg_an_positive_int(argc, argv))

		// set_nbr_philo(big_brother, argv[1])
		big_brother->nbr_philo = ft_atoi(argv[1]);
		big_brother->time_to_die = ft_atoi(argv[2]);
		big_brother->time_to_eat = ft_atoi(argv[3]);
		big_brother->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			big_brother->meal_goal = ft_atoi(argv[5]);
		else
			big_brother->meal_goal = -1;

		if (big_brother->nbr_philo < 1)
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

void init_big_brother(t_data_sim *big_brother)
{
	big_brother->philos = malloc(sizeof(pthread_t) * big_brother->nbr_philo);
	return ;
}
void *speak(t_philo *philo)
{
	printf("Je suis le PHILO d'adresse %lu, et je parle FORT\n", philo->t_pi);
	return (void *)(NULL);
}

void	init_philos(t_data_sim *big_brother)
{
	printf("Je passe la\n");
	int i;

	i = 0;
	while(i < big_brother->nbr_philo)
	{
		pthread_create(&big_brother->philos[i].t_pi, NULL, (void *)speak, &big_brother->philos[i]);
		i++;
	}
	i = 0;
	while(i < big_brother->nbr_philo)
	{
		pthread_join(big_brother->philos[i].t_pi, NULL);
		i++;
	}

}

// void	destroy_philos(t_data_sim *big_brother)
// {
// 	int i;
// 	i = 0;

// 	while (*(big_brother->philos[i])
// 	{
// 		free(big_brother->philos)
// 	}
// }
int	main(int argc, char *argv[])
{
	t_data_sim big_brother;

	if ((parsing(argc, argv, &big_brother)))
		return(1);
	init_big_brother(&big_brother);
	init_philos(&big_brother);
	// destroy_philos(&big_brother);
	// int nbr_philo;
	// nbr_philo = atoi(argv[1]);
	// if (argc >= 2)
	// {
	// 	init_ph(nbr_philo);

	printf("\n*** SIMULATION CONDITIONS ***\n");
	printf("  Number of philosopher = %d\n", big_brother.nbr_philo);
	printf("  Time to die = %d\n", big_brother.time_to_die);
	printf("  Time to eat = %d\n", big_brother.time_to_eat);
	printf("  Time to sleep = %d\n", big_brother.time_to_sleep);
	printf("  Meal goal = %d\n\n", big_brother.meal_goal);

	write(1, "PARSING OK\n", 12);
	return(0);
}