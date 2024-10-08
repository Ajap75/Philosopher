/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:37:44 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/08 16:10:19 by anastruc         ###   ########.fr       */
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
void		clean(t_monitor *monitor);
int			ft_isdigit(int c);
int			is_arg_digit(int argc, char **argv);
int			ft_atoi(const char *nptr);
int			parsing(int argc, char **argv, t_monitor *monitor);

// Clean and free : Destroy mutex and free memory allocated

void		free_everything(t_monitor *monitor);
void		destroy_mutex(t_monitor *monitor);
void		clean(t_monitor *monitor);

// Support
size_t		get_time(void);
void		printf_mutex(pthread_mutex_t *pthread_mutex);
void		print_forks(t_monitor *monitor);

int			ft_usleep(size_t millisecond);

// Initialisation
void		init_philos(t_monitor *monitor);
void		init_fork(t_monitor *monitor, t_philo *philo);
void		init_left_fork(t_philo *philo);
void		init_right_fork(t_monitor *monitor, t_philo *philo);
void		init_monitor(t_monitor *monitor, int argc, char *argv[]);

// Routine monitor
void		*routine_monitor(void *arg);
int			is_everybody_sitting(t_monitor *monitor);
void		smbd_has_eaten_enough(t_monitor *monitor);
void		who_has_eaten_enough(t_monitor *monitor);
int			who_has_died(t_monitor *monitor);

// Routine philo
void		*routine(void *arg);
void		pre_drink(t_philo *philo);
void		eat(t_philo *philo);
void		bedtime(t_philo *philo);
void		speak(t_philo *philo, int philo_statut);

// getter and setter
void		set_dead_ph_id(t_monitor *monitor, int id);
int			get_dead_ph_id(t_monitor *monitor);
void		set_has_eaten_enough(t_monitor *monitor, int has_eaten_enough);
int			get_has_eaten_enough(t_monitor *monitor);
void		set_is_sitting(t_monitor *monitor, int is_sitting);
void		i_am_sitting(t_monitor *monitor);
int			get_is_sitting(t_monitor *monitor);
void		set_symposium_state(t_monitor *monitor, int symposium_state);
int			get_symposium_state(t_monitor *monitor);
void		set_is_speaking(t_monitor *monitor, int is_speaking);
int			get_is_speaking(t_monitor *monitor);
void		set_last_meal_time(t_philo *ph, long long current_time);
long long	get_last_meal_time(t_philo *ph);
void		i_finished_lunch(t_philo *philo);
int			get_meals_eaten(t_philo *philo);
void		a_philo_has_eaten_enough(t_monitor *monitor);
void		update_fed_philos_count(t_monitor *monitor, int i);
int			get_fed_philos_count(t_monitor *monitor);

#endif
