/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivashch <sivashch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:06:42 by sivashch          #+#    #+#             */
/*   Updated: 2025/10/18 17:08:03 by sivashch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_args *args, int ph_i, char *act)
{
	long	curr_time;
	int		fin;

	pthread_mutex_lock(&args->fin_mtx);
	fin = args->fin_dining;
	pthread_mutex_unlock(&args->fin_mtx);
	curr_time = find_curr_time();
	if (fin == 0)
	{
		pthread_mutex_lock(&args->print_mtx);
		printf("%ld %d %s \n", curr_time - args->curr_time, \
				ph_i + 1, act);
		pthread_mutex_unlock(&args->print_mtx);
	}
}
