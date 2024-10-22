/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:48:09 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/22 16:11:48 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_monitor	t_monitor;

typedef struct s_symposium_veritas
{
	int						nbr_philo;
	int						time_to_die;
	int						time_to_sleep;
	int						time_to_eat;
	int						meal_target;
	unsigned long			start_time;
}							t_veritas;

typedef struct s_symposium_mutabilitas
{
	int						*full;
	int						*speak;
	int						*stop_flag;
}							t_mutabilitas;

typedef struct s_m_mutex
{
	pthread_mutex_t			full;
	pthread_mutex_t			speak;
}							t_m_mutex;

typedef struct s_ph_mutex
{
	pthread_mutex_t			lf;
	pthread_mutex_t			*rf;
	pthread_mutex_t			last_meal_time;
	pthread_mutex_t			statut;
	pthread_mutex_t			stop_flag;
}							t_ph_mutex;

/*
Each thread (Philosopher) has its own structure representing its forks.
 But in reality, he only truly owns his left fork.
He only knows the location of the right fork through the address of
the mutex that represents his neighbor's left fork.
Keep in mind that the right fork of one philosopher is the left fork
of another philosopher.
They form a circle, so to ensure they are using the same mutex, each philosopher
 has a mutex for his left fork and the address of the mutex for his right fork.
*/

typedef struct s_philo
{
	pthread_t				ph;
	int						id;
	int						stop_flag;
	int						statut;
	t_veritas				*veritas;
	int						meals_eaten;
	unsigned long			last_meal_time;
	t_ph_mutex				mutex;
	t_monitor				*monitor;
}							t_philo;

typedef struct s_monitor
{
	pthread_t				monitor;
	t_philo					*philos;
	t_mutabilitas			*mutabilitas;
	t_veritas				*veritas;
	t_m_mutex				mutex;
}							t_monitor;

/*
t_philo         *philos;       Pointer to the array of threads (philosophers)
t_mutabilitas   *mutabilitas;  Pointer to the modifiable values of the
									simulation that will evolve
t_veritas       *veritas;      Pointer to the immutable data of the simulation
t_m_mutex       mutex;         Structure of mutexes for the modifiable values
		of the simulation to protect against data races between multiple threads
*/

#endif

/* EXCALIDRAW LINK =
https://excalidraw.com/#json=aSP-cFXtHODqo-lD-4_kH,DEu99ChgbpOQVXfzuipq-Q */
