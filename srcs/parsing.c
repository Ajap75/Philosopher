/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:42:42 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/10 12:29:24 by anastruc         ###   ########.fr       */
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
		while(argv[i][j])
		{
			if (argv[i][0] == '-' || argv[i][0] == '+')
				j++;
			if (ft_isdigit(argv[i][j]) == 0)
			{
				print_error_message(1);
				return(1);
			}
			j++;
		}
		j = 0;
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

int	check_range(long arg)
{
	if (arg > INT_MAX || arg < INT_MIN)
	{
		print_error_message(2);
		return(1);
	}
	if (arg < 0)
	{
		print_error_message(2);
		return(1);
	}
	return (0);
}
int	is_empty_string(int argc, char **argv)
{
	int i;
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '\0')
		{
			print_error_message(5);
			return(1);
		}
		i++;
	}
	return(0);
}

int	check_range_of_philosopher(long nbr_philo)
{
	if (nbr_philo < 1 || nbr_philo > 200)
	{
		print_error_message(3);
		return(1);
	}
	return (0);
}

int	parsing(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc >= 5 && argc <= 6)
	{
		if (is_empty_string(argc, argv))
			return (1);
		if (is_arg_digit(argc, argv))
			return(1);
		if (check_range_of_philosopher(ft_atol(argv[1])))
			return(1);
		while (i < argc)
		{
			if (check_range(ft_atol(argv[i])))
				return(1);
			i++;
		}
	}
	else
	{
		print_error_message(4);
		return(1);
	}
	return(0);
}

// int ft_isspace(char *ptr)
// {
// 	if (*ptr >= 9 && *ptr <= 13 || *ptr == 32)
// 		return (1);
// 	return (0);
// }

// long	ft_strtol(const char *str, char **endptr, int base)
// {
// 	const char *ptr = str;
// 	long result;
// 	int sign = 1;

// 	while (isspace(*ptr))
// 		ptr++;
// 	if (*ptr == '-')
// 	{
// 		sign *= -1;
// 		ptr++;
// 	}
// 	else if (*ptr == '+')
// 		ptr++;

// }

void print_error_message (int error_code)
{
	if (error_code == 1)
		printf("\033[0;33mParsing error : Args must be digits\033[0m.\n");
	else if (error_code == 2)
		printf("\033[0;33mParsing error : Args must be stricly positive int.\033[0m\n");
	else if (error_code == 3)
		printf("\033[0;33mParsing error : The number of philosophers must be between 1 and 200 inclusive.\033[0m\n");
	else if (error_code == 4)
		printf("\033[0;33mParsing error : Not enough or too many arguments. 4 or 5 arguments required.\033[0m\n");
	else if (error_code == 5)
		printf("\033[0;33mParsing error : Empty string passed as arg\033[0m\n");
}