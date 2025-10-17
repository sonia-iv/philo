#include "philo.h"

int		ft_atoi(char *line, int *error)
{
	long	num;
	int		i;
	int		sign;

	*error = 0;
	num = 0;
	sign = 1;
	i = 0;
	if (line[0] == '-' || line[0] == '+')
	{
		if (line[0] == '-')
			sign = -1;
		i++;
	}
	while (line[i] && line[i] >= '0' && line[i] <= '9')
	{
		num = num * 10 + (line[i++] - '0');
		if (num * sign < INT_MIN || num * sign > INT_MAX)
			*error = 1;
	}
    if (line[i] != '\0')
		*error = 1;
	return ((int)num * sign);
}

int		num_of_meals_if_any(int ac, char **av, t_args *pars_args, \
		int *atoi_err)
{
	if (ac == 6)
	{
		pars_args->opt_num_of_meals = ft_atoi(av[5], atoi_err);
		if (*atoi_err || !(pars_args->opt_num_of_meals >= 1 && pars_args->opt_num_of_meals <= 200))
			return (1);
		else
			return (0);
	}
	else
		pars_args->opt_num_of_meals = -1;
	return (0);
}

int  right_fork_i(int left_i, int ph_i)
{
    int right_i;

    if (left_i == ph_i - 1)
        right_i = 0;
    else
        right_i = left_i + 1;
    return (right_i);
}