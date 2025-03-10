#include "Philosophers.h"

int main() 
{
    t_table table;
    
    init_table(&table);

    pthread_join(table.philosophers[0].thread, NULL);
    pthread_join(table.philosophers[1].thread, NULL);
    pthread_join(table.philosophers[2].thread, NULL);
    pthread_join(table.philosophers[3].thread, NULL);
    pthread_join(table.philosophers[4].thread, NULL);

    return 0;
}
