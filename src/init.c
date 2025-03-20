/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:31:38 by joafaust          #+#    #+#             */
/*   Updated: 2025/03/20 15:56:05 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	start_simulation(t_simulation *sim)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	sim->start_time = get_time_in_ms();
	while (i < sim->num_philos)
	{
		pthread_create(&sim->philos[i].thread, NULL, philosopher_routine,
			&sim->philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, sim);
	i = 0;
	while (i < sim->num_philos)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

void	init_simulation(t_simulation *sim, int argc, char **argv)
{
	int	i;

	i = 0;
	sim->num_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->must_eat_count = ft_atoi(argv[5]);
	else
		sim->must_eat_count = -1;
	sim->stop = 0;
	sim->forks = malloc(sim->num_philos * sizeof(pthread_mutex_t));
	sim->philos = malloc(sim->num_philos * sizeof(t_philo));
	pthread_mutex_init(&sim->print_lock, NULL);
	while (i < sim->num_philos)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < sim->num_philos)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1) % sim->num_philos];
		sim->philos[i].last_meal_time = get_time_in_ms();
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].sim = sim;
		i++;
	}
}

void	cleanup_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->print_lock);
	free(sim->forks);
	free(sim->philos);
}
