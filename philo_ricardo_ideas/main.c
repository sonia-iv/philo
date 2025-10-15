#include "philo.h"

int main(int ac, char **av)
{
	t_args	args;
	t_philo	*ph;

	ph = NULL;
	memset(&args, 0, sizeof(t_args));
	if (init_verif_args(ac, av, &args))
		return (1);
	if (init_philos(&ph, &args))
		return (1);
	if (philos_dining(ph, &args))
		return (1);
	return (0);
}