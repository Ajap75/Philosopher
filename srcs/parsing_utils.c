/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:20:26 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/16 14:48:15 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

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
		j = 0;
		while(argv[i][j])
		{
			if (argv[i][j] == '-' || argv[i][j] == '+')
				j++;
			if (ft_isdigit(argv[i][j]) == 0)
			{
				print_error_message(1);
				return(1);
			}
			j++;
		}
		i++;
	}
	return(0);
}

long	ft_atol(const char *nptr)
{
	int	sign;
	long	result;
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
