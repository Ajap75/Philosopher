/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:42:42 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/18 11:58:42 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

int	check_range(long arg)
{
	if (arg > INT_MAX || arg < INT_MIN)
	{
		print_error_message(2);
		return (1);
	}
	if (arg < 0)
	{
		print_error_message(2);
		return (1);
	}
	return (0);
}

int	is_empty_string(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '\0')
		{
			print_error_message(5);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_arguments_range(long nbr_philo, long eat_time, long sleep_time)
{
	if (nbr_philo < 1 || nbr_philo > 200)
	{
		print_error_message(3);
		return (1);
	}
	if (eat_time < 60 || sleep_time < 60)
	{
		print_error_message(6);
		return (1);
	}
	return (0);
}

int	parsing(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc >= 5 && argc <= 6)
	{
		if (is_empty_string(argc, argv))
			return (1);
		if (is_arg_digit(argc, argv))
			return (1);
		if (check_arguments_range(ft_atol(argv[1]), ft_atol(argv[3]),
				ft_atol(argv[4])))
			return (1);
		while (i < argc)
		{
			if (check_range(ft_atol(argv[i])))
				return (1);
			i++;
		}
	}
	else
	{
		print_error_message(4);
		return (1);
	}
	return (0);
}

void	print_error_message(int error_code)
{
	if (error_code == 1)
		printf("\033[0;33mParsing error : Args must be integer\033[0m.\n");
	else if (error_code == 2)
		printf("\033[0;33mParsing error : Args must be stricly positive int.\033[0m\n");
	else if (error_code == 3)
		printf("\033[0;33mParsing error : The number of philosophers must be between 1 and 200 inclusive.\033[0m\n");
	else if (error_code == 4)
		printf("\033[0;33mParsing error : Not enough or too many arguments. 4 or 5 arguments required.\033[0m\n");
	else if (error_code == 5)
		printf("\033[0;33mParsing error : Empty string passed as arg\033[0m\n");
	else if (error_code == 6)
		printf("\033[0;33mParsing error : Sleep and eat time must be greater than 60ms inclusive.\033[0m\n");
	else if (error_code == 7)
		printf("\033[0;33mMALLOC ERROR.\033[0m\n");
	else if (error_code == 8)
		printf("\033[0;33mMUTEX_INIT_ERROR.\033[0m\n");
	else if (error_code == 9)
		printf("\033[0;33mTHREAD_INIT_ERROR.\033[0m\n");
}

