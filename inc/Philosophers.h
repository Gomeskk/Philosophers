#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define NUM_PHILOSOPHERS 5

typedef struct s_philosopher {
    int id;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
} t_philosopher;

typedef struct s_table {
    t_philosopher philosophers[NUM_PHILOSOPHERS];
    pthread_mutex_t forks[NUM_PHILOSOPHERS];
} t_table;

void think(int id);
void eat(t_philosopher *philo);
void *philosopher_routine(void *arg);
void init_table(t_table *table);