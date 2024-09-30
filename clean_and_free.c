/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:35:04 by anastruc          #+#    #+#             */
/*   Updated: 2024/09/30 13:38:05 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "function.h"

void	clean(t_monitor *monitor)
{
	int	i;
	i = 0;

	// if (monitor->mutabilitas != NULL)
	// 	free(monitor->mutabilitas);

	if (monitor->veritas != NULL)
		free(monitor->veritas);

	if(monitor->philos != NULL)
		free(monitor->philos);
	// free(monitor);
}