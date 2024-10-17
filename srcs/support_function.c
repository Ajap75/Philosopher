/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:06:59 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/17 11:42:36 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

int	ft_usleep(size_t millisecond)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < millisecond)
	{
		usleep(10);
	}
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return (((long long)current_time.tv_sec * 1000) + (current_time.tv_usec
			/ 1000));
}