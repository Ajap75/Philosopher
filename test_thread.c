/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:26:03 by anastruc          #+#    #+#             */
/*   Updated: 2024/09/24 15:42:26 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void	*roll_dice()
{
	int	value;
	int	*result;

	value = (rand() % 6) + 1;
	result = malloc(sizeof(int));
	printf("%d\n", value);
	printf("thread result address = %p\n", result);
	*result = value;
	return (void *) (result);
}
int	main(void)
{
	int *res;
	srand(time(NULL));
	pthread_t p1;
	if (pthread_create(&p1, NULL, &roll_dice, NULL) != 0)
		return (1);
	if (pthread_join(p1, (void **)&res) != 0)
		return (2);
	printf("Result: %d\n", *res);
	printf("Main result address = %p\n", res);

	return (0);
}