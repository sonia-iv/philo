/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivashch <sivashch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:32:29 by sivashch          #+#    #+#             */
/*   Updated: 2025/10/18 16:59:01 by sivashch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_args	t_args;
typedef struct s_philo	t_philo;

/// @brief const values that we read from main
/*
    num_of_philo -> from 1 to 200
    ttd -> >= 60;
    tte -> >= 60;
    tts -> >= 60;
    opt_num = -1 if not init
    start... -> gettimeof the day;
*/
struct	s_args
{
	int				ph_nb;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				opt_num_of_meals;
	long			curr_time;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*ph_mtx;
	pthread_mutex_t	fin_mtx;
	int				fin_dining;
	int				ph_fed;
};

struct	s_philo
{
	t_args		*args;
	int			ph_i;
	int			left_fork;
	int			right_fork;
	long		last_meal_time;
	int			meals_cnt;
	pthread_t	thread_ph;
};

// ===========================================================
// 							UTILS_INIT
// ===========================================================

int		ft_atoi(char *line, int *error);
int		num_of_meals_if_any(int ac, char **av, t_args *pars_args, \
		int *atoi_err);
int		right_fork_i(int left_i, int ph_i);

// ===========================================================
// 							INIT
// ===========================================================

int		init_args_mtx(t_args *args);
int		init_verif_args(int ac, char **av, t_args *pars_args);
int		init_philos(t_philo **ph, t_args *args);

// ===========================================================
// 							TIME_FUNCTNS
// ===========================================================

long	find_curr_time(void);

// ===========================================================
// 							UTILS_ROUTINE
// ===========================================================

void	print_action(t_args *args, int ph_i, char *act);

// ===========================================================
// 							PHILO_ROUTINE
// ===========================================================

void	wait_while(long time_of_act, t_args *args);
void	which_fork_to_pick(t_philo *ph, int *fir, int *sec);
void	ph_eating(t_philo *ph, t_args *args);

// ===========================================================
// 							PHILOS_DINING
// ===========================================================

void	*thread_routine(void *arg);
int		philos_dining(t_philo *ph, t_args *args);

// ===========================================================
// 							PHILOS_DINING
// ===========================================================

void	philo_finish_dining(t_philo *ph, t_args *args);
void	free_thread_destroy_mutex(t_philo *ph, t_args *args);

// ===========================================================
// 							PRINT_MSG
// ===========================================================

// Temporary utils
void	print_args(const t_args *pars_args);
void	print_philos(t_args *args, t_philo *ph);

#endif
