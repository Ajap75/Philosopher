/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:40:42 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/16 11:46:20 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/function.h"
#include "../headers/structure.h"

void	printf_forks(pthread_mutex_t *pthread_mutex)
{
	printf("Mutex adress = %p\n", (void *)pthread_mutex);
}
void	print_forks(t_monitor *monitor)
{
	int i;
	i = 0;

	while(i < monitor->veritas->nbr_philo)
	{
		printf("\n");
		printf("la fourchette de gauche de %d est : ", monitor->philos[i].id);
		printf_forks(&monitor->philos[i].mutex.lf);
		printf("la fourchette de droite de %d est : ", monitor->philos[i].id);
		printf_forks(monitor->philos[i].mutex.rf);
		printf("\n");
		i++;
	}
}