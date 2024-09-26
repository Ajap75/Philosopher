/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:48:09 by anastruc          #+#    #+#             */
/*   Updated: 2024/09/26 17:58:36 by anastruc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t	ph;
	int			id;
	int			status;
	t_veritas 	veritas; //pointeur vers les datas immutable de la simulations
}				t_philo;

typedef struct s_monitor
{
	pthread_t		monitor;
	t_philo			*philos; // pointeur vers tableau des threads (philosopher)
	t_mutabilitas	*mutabilitas; //pointeur vers
	t_veritas		*veritas;
	t_m_mutex		mutex;
}				t_monitor;

typedef struct s_symposium_veritas
{
	int			nbr_philo;
	int			time_to_die;
	int			time_to_sleep;
	int			time_to_eat;
	int			meal_target;
	int			start_time;
}				t_veritas;

typedef struct s_symposium_mutabilitas
{
	int			*dead_ph_id;
	int			*has_eaten_enough;
	int			*is_sitting;
	int			*symposium_state;
	int			*is_speaking; // a philosopher (thread) is saying something, I'm eating...
}				t_mutabilitas;

typedef struct s_m_mutex
{
	pthread_mutex_t print;
	pthread_mutex_t dead_ph;
	pthread_mutex_t has_eaten_enough;
	pthread_mutex_t is_sitting;
	pthread_mutex_t symposium_state; // DEAD, READY,
}				t_m_mutex;

typedef struct s_ph_mutex
{
	pthread_mutex_t lf;
	pthread_mutex_t	*rf; // Chaque thread (Philosopher) a sa propre structure representant ses fourchettes. Mais en realite il n'a que la fourchette de gauche qui lui appartint reellement,
						//	la fourchette de droite il ne connait que son emplacement grace a l'adresse du Mutex qui represente la fourchette de gauche de son voisin.
						// A garder en tete que la fourchette de droite de l'un des philosopher est la fourchette de gauche d'un autre philosopher.
	 					 // Il forme un cercle, donc pour que l'on soitd sur le meme mutex, donc chacun des philos a un mutex sur sa fourchette de droite, et l'adresse du mutex de sa fourchette de gauche).
}				t_ph_mutex;




#endif

// EXCALIDRAW LINK = https://excalidraw.com/#json=aSP-cFXtHODqo-lD-4_kH,DEu99ChgbpOQVXfzuipq-Q
// To do : Fonction d'initialisation (monitor, fourchette, philo)
// Fonction pour recuperer l'heure et la conversion exacte sans ecart en milliseconde
// Finir parsing avec nottamment le blocage des overflow et des debordement. 