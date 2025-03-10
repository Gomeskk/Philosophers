#include "Philosophers.h"

void think(int id) 
{
    printf("Philosopher %d is thinking\n", id);
    usleep(1000 * (rand() % 500)); //simulating thinking time
    //rand() % 500 generates a random number between 0 and 499.
    //1000 * (rand() % 500) converts it into microseconds (between 0 and 499,000 microseconds).
}

void eat(t_philosopher *philo) 
{
    pthread_mutex_lock(philo->left_fork);//pick up left fork
    pthread_mutex_lock(philo->right_fork);//pick up right fork
    
    printf("Philosopher %d is eating\n", philo->id);
    usleep(1000 * (rand() % 500)); //simulating eating time
    
    pthread_mutex_unlock(philo->right_fork);//put down right fork
    pthread_mutex_unlock(philo->left_fork);//put down left fork
}

void *philosopher_routine(void *arg) 
{
    t_philosopher *philo = (t_philosopher *)arg;

    while (1)//infinite loop
    {
        think(philo->id);
        eat(philo);
    }
    return NULL;
}
