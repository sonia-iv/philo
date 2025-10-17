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
        usleep(100);
    }
}
void which_fork_to_pick(t_philo *ph, int *fir, int *sec)
{
    if (ph->ph_i % 2 == 0)
    {
        *fir = ph->left_fork;
        *sec = ph->right_fork;
    }
    else
    {
        *fir = ph->right_fork;
        *sec = ph->left_fork;
    }
}
void ph_eating(t_philo *ph, t_args *args)
{
    int fir;
    int sec;

    which_fork_to_pick(ph, &fir, &sec);
    pthread_mutex_lock(&args->forks[fir]);
    print_action(args, ph->ph_i, "has taken a fork");
    if (args->ph_nb != 1)
    {
        pthread_mutex_lock(&args->forks[sec]);
        print_action(args, ph->ph_i, "has taken a fork");
        pthread_mutex_lock(&args->ph_mtx[ph->ph_i]);
        ph->last_meal_time = find_curr_time();
        ph->meals_cnt += 1;
        pthread_mutex_unlock(&args->ph_mtx[ph->ph_i]);
        print_action(args, ph->ph_i, "is eating");
        wait_while(args->time_to_eat, args);
        pthread_mutex_unlock(&args->forks[sec]);
    }
    else
        wait_while(args->time_to_die, args);
    pthread_mutex_unlock(&args->forks[fir]);
}


    /*if (ph->ph_i % 2 == 0)
    {
        fir = ph->left_fork;
        sec = ph->right_fork;
    }
    else
    {
        fir = ph->right_fork;
        sec = ph->left_fork;
    }*/
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

/*void ph_eating(t_philo *ph, t_args *args)
{
    int fir_fork, sec_fork;

    if (args->ph_nb == 1)
    {
        pthread_mutex_lock(&args->forks[ph->left_fork]);
        print_action(args, ph->ph_i, "has taken a fork");
        wait_while(args->time_to_die, args);
        pthread_mutex_unlock(&args->forks[ph->left_fork]);
        return;
    }
    if (ph->ph_i % 2 == 0)
    {
        fir_fork = ph->left_fork;
        sec_fork = ph->right_fork;
    }
    else
    {
        fir_fork = ph->right_fork;
        sec_fork = ph->left_fork;
    }
    pthread_mutex_lock(&args->forks[fir_fork]);
    print_action(args, ph->ph_i, "has taken a fork");
    pthread_mutex_lock(&args->forks[sec_fork]);
    print_action(args, ph->ph_i, "has taken a fork");
    pthread_mutex_lock(&args->ph_mtx[ph->ph_i]);
    ph->last_meal_time = find_curr_time();
    ph->meals_cnt += 1;
    pthread_mutex_unlock(&args->ph_mtx[ph->ph_i]);
    print_action(args, ph->ph_i, "is eating");
    wait_while(args->time_to_eat, args);
    pthread_mutex_unlock(&args->forks[sec_fork]);
    pthread_mutex_unlock(&args->forks[fir_fork]);
}*/
