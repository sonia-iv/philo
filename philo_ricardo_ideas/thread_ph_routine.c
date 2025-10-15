#include "philo.h"

void    wait_while(long time_of_act, t_args *args)
{
    long    start_of_sim;
    long    curr_time;
    int     fin;

    start_of_sim = find_curr_time();
    while (1)
    {
        pthread_mutex_lock(&args->fin_mtx);
        fin = args->fin_dining;
        pthread_mutex_unlock(&args->fin_mtx);
        if (fin)
            break ;
        curr_time = find_curr_time();
        if ((curr_time - start_of_sim) >= time_of_act)
            break ;
        usleep(1000);
    }
}

void ph_eating(t_philo *ph, t_args *args)
{
    int first;
    int second;

    if (ph->left_fork < ph->right_fork)
    {
        first = ph->left_fork;
        second = ph->right_fork;
    }
    else
    {
        first = ph->right_fork;
        second = ph->left_fork;
    }

    pthread_mutex_lock(&args->forks[first]);
    print_action(args, ph->ph_i, "has taken a fork");
    if (args->ph_nb != 1)
    {
        pthread_mutex_lock(&args->forks[second]);
        print_action(args, ph->ph_i, "has taken a fork");
        print_action(args, ph->ph_i, "is eating");
        pthread_mutex_lock(&args->ph_mtx[ph->ph_i]);
        ph->last_meal_time = find_curr_time();
        ph->meals_cnt += 1;
        pthread_mutex_unlock(&args->ph_mtx[ph->ph_i]);
        wait_while(args->time_to_eat, args);
        pthread_mutex_unlock(&args->forks[second]);
    }
    else
        wait_while(args->time_to_die, args);
    pthread_mutex_unlock(&args->forks[first]);
}

/*void    ph_eating(t_philo *ph, t_args *args)
{
    pthread_mutex_lock(&args->forks[ph->left_fork]);
    print_action(args, ph->ph_i, "has taken a fork");
    if (args->ph_nb != 1)
    {
        pthread_mutex_lock(&args->forks[ph->right_fork]);
        print_action(args, ph->ph_i, "has taken a fork");
        print_action(args, ph->ph_i, "is eating");
        pthread_mutex_lock(&args->ph_mtx[ph->ph_i]);
        ph->last_meal_time = find_curr_time();
        ph->meals_cnt = ph->meals_cnt + 1;
        pthread_mutex_unlock(&args->ph_mtx[ph->ph_i]);
        wait_while(args->time_to_eat, args);
        pthread_mutex_unlock(&args->forks[ph->right_fork]);
    }
    else
        wait_while(args->time_to_die, args);
    pthread_mutex_unlock(&args->forks[ph->left_fork]);
}*/