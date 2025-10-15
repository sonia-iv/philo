#include "philo.h"

void    *thread_routine(void *arg)
{
    t_args  *args;
    t_philo *ph;
    int     fin;

    fin = 0;
    ph = arg;
    args = ph->args;
    if (ph->ph_i % 2 != 0)
        usleep(args->time_to_eat * 500);
    while (fin == 0)
    {
        ph_eating(ph, args);
        print_action(args, ph->ph_i, "is sleeping");
        wait_while(args->time_to_sleep, args);
        print_action(args, ph->ph_i, "is thinking");
        pthread_mutex_lock(&args->fin_mtx);
        fin = args->fin_dining;
        pthread_mutex_unlock(&args->fin_mtx);
    }
    return (0);
}

int     philos_dining(t_philo *ph, t_args *args)
{
    int i;
    
    i = 0;
    while (i < args->ph_nb)
    {
        ph[i].last_meal_time = find_curr_time();
        if (pthread_create(&ph[i].thread_ph, NULL, \
                            thread_routine, &ph[i]))
            return (1);
        i++;
    }
    philo_finish_dining(ph, args);
    i = 0;
    while (i < args->ph_nb)
    {
        if (pthread_join(ph[i++].thread_ph, NULL) != 0)
            return (1);
    }
    free_thread_destroy_mutex(ph, args);
    return (0);
}
