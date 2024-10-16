/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:37:44 by anastruc          #+#    #+#             */
/*   Updated: 2024/10/18 15:29:13 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H
# define EATING 1
# define SLEEPING 2
# define HAS_TAKEN_A_FORK 15
# define START_ACTION 3
# define END_ACTION 4
# define THINKING 5
# define READY 12
# define STOP 13
# define APERO 14
# define ALIVE 10
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
int				is_everybody_sitting(t_monitor *monitor);
void			smbd_has_eaten_enough(t_monitor *monitor);
void			who_has_eaten_enough(t_monitor *monitor);
int				who_has_died(t_monitor *monitor);

// Routine philo
void			*routine(void *arg);
void			pre_drink(t_philo *philo);
void			think(t_philo *philo);
void			eat(t_philo *philo);
void			even_philo_eat(t_philo *philo);
void			odd_philo_eat(t_philo *philo);
void			bedtime(t_philo *philo);
void			speak(t_philo *philo, int philo_statut);
int				am_i_alive(t_philo *philo);
int				get_life_statut(t_philo *philo);

void			secure_print(char *s, t_philo *philo, char *color,
					int end_flag);

// getter and setter

void			set_has_eaten_enough(t_monitor *monitor, int has_eaten_enough);
int				get_has_eaten_enough(t_monitor *monitor);
void			set_is_sitting(t_monitor *monitor, int is_sitting);
void			i_am_sitting(t_monitor *monitor);
int				get_is_sitting(t_monitor *monitor);
void			set_symposium_state(t_monitor *monitor, int symposium_state);
int				get_symposium_state(t_monitor *monitor);
void			set_last_meal_time(t_philo *ph, long long current_time);
long long		get_last_meal_time(t_philo *ph);
void			i_finished_lunch(t_philo *philo);
int				get_meals_eaten(t_philo *philo);
void			a_philo_has_eaten_enough(t_monitor *monitor);
void			update_fed_philos_count(t_monitor *monitor, int i);
int				get_fed_philos_count(t_monitor *monitor);
void			take_right_fork_first(t_philo *philo);
void			take_left_fork_first(t_philo *philo);

// test

void			print_symp_info(t_monitor *monitor);
void			printf_forks(pthread_mutex_t *pthread_mutex);
void			print_symp_info(t_monitor *monitor);
void			print_mess(char *message, int philo, t_monitor *monitor);

#endif
