/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:06:59 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/10 17:22:13 by anastruc         ###   ########.fr       */
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
		usleep(1);
	}
	return (0);
}

size_t	get_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return (((long long)current_time.tv_sec * 1000) + (current_time.tv_usec
			/ 1000));
}