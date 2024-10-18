/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:40:42 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/18 12:51:07 by anastruc         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (i < monitor->veritas->nbr_philo)
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

void	print_symp_info(t_monitor *monitor)
{
	printf("\n \033[0;33m*** Monitor informtions ***\033[0m\n");
	printf("  How many philoophers are sitting ? = %d\n",
		*monitor->mutabilitas->is_sitting);
	printf("  How many philoophers are speaking ? = %d\n",
		*monitor->mutabilitas->is_speaking);
	printf("  Status of the symposium state? = %d\n",
		*monitor->mutabilitas->symposium_state);
	printf("  How many philosophers has eatten enough? = %d\n",
		*monitor->mutabilitas->has_eaten_enough);
}

void	print_mess(char *message, int philo, t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->mutex.is_speaking);
	printf("// %s%d%s // %s\n", RED, philo, RESET, message);
	pthread_mutex_unlock(&monitor->mutex.is_speaking);
}
