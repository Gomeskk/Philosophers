#include "Philosophers.h"

void init_table(t_table *table) 
{
    int i = 0;

    pthread_mutex_init(&table->forks[i], NULL);
    i++;
    pthread_mutex_init(&table->forks[i], NULL);
    i++;
    pthread_mutex_init(&table->forks[i], NULL);
    i++;
    pthread_mutex_init(&table->forks[i], NULL);
    i++;
    pthread_mutex_init(&table->forks[i], NULL);

    i = 0;
    table->philosophers[i].id = i;
    table->philosophers[i].left_fork = &table->forks[i];
    table->philosophers[i].right_fork = &table->forks[i + 1];
    pthread_create(&table->philosophers[i].thread, NULL, philosopher_routine, &table->philosophers[i]);

    i = 1;
    table->philosophers[i].id = i;
    table->philosophers[i].left_fork = &table->forks[i];
    table->philosophers[i].right_fork = &table->forks[i + 1];
    pthread_create(&table->philosophers[i].thread, NULL, philosopher_routine, &table->philosophers[i]);

    i = 2;
    table->philosophers[i].id = i;
    table->philosophers[i].left_fork = &table->forks[i];
    table->philosophers[i].right_fork = &table->forks[i + 1];
    pthread_create(&table->philosophers[i].thread, NULL, philosopher_routine, &table->philosophers[i]);

    i = 3;
    table->philosophers[i].id = i;
    table->philosophers[i].left_fork = &table->forks[i];
    table->philosophers[i].right_fork = &table->forks[i + 1];
    pthread_create(&table->philosophers[i].thread, NULL, philosopher_routine, &table->philosophers[i]);

    i = 4;
    table->philosophers[i].id = i;
    table->philosophers[i].left_fork = &table->forks[i];
    table->philosophers[i].right_fork = &table->forks[0];//wrap-around for last philosopher
    pthread_create(&table->philosophers[i].thread, NULL, philosopher_routine, &table->philosophers[i]);
}
