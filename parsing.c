/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:42:42 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/01 12:27:24 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "function.h"

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