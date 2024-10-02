/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:37:44 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/02 13:47:53 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H
# define EATING 1
# define SLEEPING 2
# define START_ACTION 3
# define END_ACTION 4
# define THINKING 5
# define READY 6
# define STOP 7
# define APERO 8

# include "structure.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// Parsing
void	clean(t_monitor *monitor);
int		ft_isdigit(int c);
int		is_arg_digit(int argc, char **argv);
int		ft_atoi(const char *nptr);
int		parsing(int argc, char **argv, t_monitor *monitor);

// Support
int		get_time(void);

// Initialisation
void	init_philos(t_monitor *monitor);
int		init_fork(t_monitor *monitor, t_philo *philo);
void	init_monitor(t_monitor *monitor, int argc, char *argv[]);

// Routine monitor
void	*routine_monitor(void *arg);
int		is_everybody_sitting(t_monitor *monitor);

// Routine philo
void	*routine(void *arg);
void	eat(t_philo *philo);
void	bedtime(t_philo *philo);
void	speak(t_philo *philo, int action, int statut);

// getter and setter
void	set_dead_ph_id(t_monitor *monitor, int id);
int	get_dead_ph_id(t_monitor *monitor);
void	set_has_eaten_enough(t_monitor *monitor, int has_eaten_enough);
int	get_has_eaten_enough(t_monitor *monitor);
void	set_is_sitting(t_monitor *monitor, int is_sitting);
int	get_is_sitting(t_monitor *monitor);
void	set_symposium_state(t_monitor *monitor, int symposium_state);
int	get_symposium_state(t_monitor *monitor);
void	set_is_speaking(t_monitor *monitor, int is_speaking);
int	get_is_speaking(t_monitor *monitor);

#endif

