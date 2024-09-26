/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:26:03 by anastruc          #+#    #+#             */
/*   Updated: 2024/09/24 11:38:33 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main (void)
{
	int x = 2;
	int pid = fork();
	if (pid == -1)
		return (1);
	printf("process ID = %d\n", getpid());
	printf("Hello World from process\n");
	if (pid == 0)
		x++;
	sleep(2);
	printf("X  = %d\n", x);
	if (pid != 0)
	{
		wait(NULL);
	}
	return (0);
}