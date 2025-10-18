/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivashch <sivashch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:16:26 by sivashch          #+#    #+#             */
/*   Updated: 2025/10/17 19:23:16 by sivashch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args_mtx(t_args *args)
{
	int	i;

	if (pthread_mutex_init(&args->print_mtx, NULL))
		return (1);
	if (pthread_mutex_init(&args->fin_mtx, NULL))
		return (1);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->ph_nb);
	args->ph_mtx = malloc(sizeof(pthread_mutex_t) * args->ph_nb);
	if (!args->forks || !args->ph_mtx)
		return (1);
	i = 0;
	while (i < args->ph_nb)
	{
		if (pthread_mutex_init(&args->forks[i], NULL))
			return (1);
		if (pthread_mutex_init(&args->ph_mtx[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

/*	print_args(pars_args); before init mutex*/
int	init_verif_args(int ac, char **av, t_args *pars_args)
{
	int	atoi_err;

	if (ac != 5 && ac != 6)
		return (write(2, "Error: wrong number of args\n", 29), 1);
	pars_args->ph_nb = ft_atoi(av[1], &atoi_err);
	if (atoi_err || !(pars_args->ph_nb >= 1 && pars_args->ph_nb <= 200))
		return (write(2, "Error: wrong num_of_philos\n", 27), 1);
	pars_args->time_to_die = ft_atoi(av[2], &atoi_err);
	if (atoi_err || pars_args->time_to_die < 60)
		return (write(2, "Error: another ttd expected\n", 28), 1);
	pars_args->time_to_eat = ft_atoi(av[3], &atoi_err);
	if (atoi_err || pars_args->time_to_eat < 60)
		return (write(2, "Error: another tte expected\n", 28), 1);
	pars_args->time_to_sleep = ft_atoi(av[4], &atoi_err);
	if (atoi_err || pars_args->time_to_sleep < 60)
		return (write(2, "Error: another tts expected\n", 28), 1);
	if (num_of_meals_if_any(ac, av, pars_args, &atoi_err) == 1)
		return (write(2, "Error: wrong num_of_meals\n", 27), 1);
	pars_args->curr_time = find_curr_time();
	if (init_args_mtx(pars_args))
		return (1);
	return (0);
}

/*print_philos(args, *ph) before return*/
int	init_philos(t_philo **ph, t_args *args)
{
	int	i;

	i = 0;
	*ph = malloc(sizeof(t_philo) * args->ph_nb);
	if (!*ph)
		return (1);
	while (i < args->ph_nb)
	{
		(*ph)[i].args = args;
		(*ph)[i].ph_i = i;
		(*ph)[i].left_fork = i;
		(*ph)[i].right_fork = right_fork_i(i, args->ph_nb);
		(*ph)[i].last_meal_time = find_curr_time();
		(*ph)[i].meals_cnt = 0;
		i++;
	}
	return (0);
}

/*void	print_args(const t_args *pars_args)
{
	printf("av[1]=%d\n", pars_args->ph_nb);
	printf("av[2]=%ld\n", pars_args->time_to_die);
	printf("av[3]=%ld\n", pars_args->time_to_eat);
	printf("av[4]=%ld\n", pars_args->time_to_sleep);
	if (pars_args->opt_num_of_meals != -1)
		printf("av[5]=%d\n", pars_args->opt_num_of_meals);
	printf("curr_time: %ld\n", pars_args->curr_time);
}

void	print_one_philo(const t_philo *ph)
{
	printf("philo[%d]: left=%d right=%d last_meal=%ld meals=%d args %p\n",
		ph->ph_i, ph->left_fork, ph->right_fork, \
		ph->last_meal_time, ph->meals_cnt, (void *)ph->args);
}

void	print_philos(t_args *args, t_philo *ph)
{
	int	i;

	i = 0;
	while (i < args->ph_nb)
	{
		print_one_philo(&ph[i]);
		i++;
	}
}*/
