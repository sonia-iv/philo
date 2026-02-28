/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sivashch <sivashch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:08:15 by sivashch          #+#    #+#             */
/*   Updated: 2025/10/18 17:08:59 by sivashch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief 1 sec = 1000 ms, 1 µs = 0.001 ms
/// @param
/// @return value in milliseconds
/* int gettimeofday(struct timeval *tv, struct timezone *tz);*/
long	find_curr_time(void)
{
	struct timeval	tv;
	long			curr_time;
	long			sec;
	long			microsec;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec;
	microsec = tv.tv_usec;
	curr_time = ((sec * 1000) + (microsec / 1000));
	return (curr_time);
}
