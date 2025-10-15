#include "philo.h"

/*void    philo_finish_dining(t_philo *ph, t_args *args)
{
    int     i;
    long    curr;

    while (args->fin_dining == 0)
    {
        if ((args->opt_num_of_meals != 0) && (args->ph_nb == args->ph_fed))
        {
            args->fin_dining = 1;
            break ;
        }
        i = 0;
        while (i < args->ph_nb)
        {
            curr = find_curr_time();
            if ((curr - ph[i].last_meal_time) >= args->time_to_die)
            {
                print_action(args, i, "died");
                args->fin_dining = 1;
                break ;
            }
            i++;
        }
    }
}*/

void    philo_finish_dining(t_philo *ph, t_args *args)
{
    int     all_fin_din;
    long    curr;
    int     i;
    long    last_meal;

    while (1)
    {
        pthread_mutex_lock(&args->fin_mtx);
        if (args->fin_dining)
        {
            pthread_mutex_unlock(&args->fin_mtx);
            break ;
        }
        pthread_mutex_unlock(&args->fin_mtx);
        all_fin_din = (args->opt_num_of_meals > 0);
        curr = find_curr_time();
        i = 0;
        while (i < args->ph_nb)
        {
            pthread_mutex_lock(&args->ph_mtx[i]);
            last_meal = ph[i].last_meal_time;
            if (args->opt_num_of_meals > 0
                && ph[i].meals_cnt < args->opt_num_of_meals)
                all_fin_din = 0;
            pthread_mutex_unlock(&args->ph_mtx[i]);
            if (curr - last_meal >= args->time_to_die)
            {
                print_action(args, i, "died");
                pthread_mutex_lock(&args->fin_mtx);
                args->fin_dining = 1;
                pthread_mutex_unlock(&args->fin_mtx);
                break ;
            }
            i++;
        }
        if (all_fin_din)
        {
            pthread_mutex_lock(&args->fin_mtx);
            args->fin_dining = 1;
            pthread_mutex_unlock(&args->fin_mtx);
        }
        usleep(200);
    }
}


void    free_thread_destroy_mutex(t_philo *ph, t_args *args)
{
    int i;

    i = -1;
    while (++i < args->ph_nb)
    {
        pthread_mutex_destroy(&args->forks[i]);
        pthread_mutex_destroy(&args->ph_mtx[i]);
    }
    free(args->forks);
    free(args->ph_mtx);
    pthread_mutex_destroy(&args->fin_mtx);
    pthread_mutex_destroy(&args->print_mtx);
    free(ph);
}