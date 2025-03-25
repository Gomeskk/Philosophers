/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:31:47 by joafaust          #+#    #+#             */
/*   Updated: 2025/03/25 00:38:38 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	print_action(t_simulation *sim, int id, char *action)
{
	pthread_mutex_lock(&sim->print_lock);
	if (!sim->stop)
		printf("%ld %d %s\n", get_time_in_ms() - sim->start_time, id, action);
	pthread_mutex_unlock(&sim->print_lock);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->sim->num_philos == 1)
	{
		handle_one_philosopher(philo);
		return (NULL);
	}
	wait_for_turn(philo);
	while (!philo->sim->stop)
	{
		usleep(100);
		eat(philo);
		if (has_eaten_enough(philo))
			break ;
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	while (!sim->stop)
	{
		check_deaths(sim);
		if (sim->stop)  // Exit if someone died
			return (NULL);
		check_all_eaten(sim);
		usleep(100);
	}
	return (NULL);
}

