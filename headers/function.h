/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:37:44 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/23 11:23:26 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H
# define EATING 1
# define SLEEPING 2
# define HAS_TAKEN_A_FORK 15
# define THINKING 5
# define DEAD 11
# define MALLOC_ERROR 7
# define MUTEX_INIT_ERROR 8
# define THREAD_INIT 9
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define RED "\033[0;31m"
# define RESET "\033[0m"

# include "structure.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// Parsing
void			clean(t_monitor *monitor);
int				ft_isdigit(int c);
int				is_arg_digit(int argc, char **argv);
long			ft_atol(const char *nptr);
int				parsing(int argc, char **argv);
void			print_error_message(int error_code);
int				is_empty_string(int argc, char **argv);
int				check_arguments_range(long nbr_philo, long eat_time,
					long sleep_time);

// Clean and free : Destroy mutex and free memory allocated

void			free_everything(t_monitor *monitor);
void			destroy_mutex(t_monitor *monitor);
void			clean(t_monitor *monitor);

// Support
unsigned long	get_time(void);
void			printf_mutex(pthread_mutex_t *pthread_mutex);
void			print_forks(t_monitor *monitor);

int				ft_usleep(unsigned long millisecond);

// Initialisation

int				init_philos(t_monitor *monitor);
int				ft_malloc(t_monitor *monitor);
int				init_philo_thread(t_monitor *monitor);
int				init_philo_mutex(t_monitor *monitor, int i);
int				init_fork(t_monitor *monitor, t_philo *philo);
int				init_left_fork(t_philo *philo);
void			init_right_fork(t_monitor *monitor, t_philo *philo);
int				init_monitor(t_monitor *monitor, int argc, char *argv[]);
int				init_monitor_mutex(t_monitor *monitor);

// Routine monitor
void			*routine_monitor(void *arg);
void			is_everybody_full(t_monitor *monitor);
int				who_has_died(t_monitor *monitor);
void			stop_flag(t_monitor *monitor);

// Routine philo
void			*routine(void *arg);
void			pre_drink(t_philo *philo);
void			think(t_philo *philo);
void			i_am_alone(t_philo *philo);
void			eat(t_philo *philo);
void			even_philo_eat(t_philo *philo);
void			odd_philo_eat(t_philo *philo);
void			bedtime(t_philo *philo);
int				am_i_dead(t_philo *philo);
void			speak(t_philo *philo, int philo_statut);
void			secure_print(char *s, t_philo *philo, char *color);
void			secure_print_death(char *s, t_philo *philo, char *color);

// getter and setter

void			set_last_meal_time(t_philo *ph, long long current_time);
long long		get_last_meal_time(t_philo *ph);
void			i_finished_lunch(t_philo *philo);
void			take_right_fork_first(t_philo *philo);
void			take_left_fork_first(t_philo *philo);

// test

void			printf_forks(pthread_mutex_t *pthread_mutex);

#endif
