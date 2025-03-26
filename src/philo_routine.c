/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:31:47 by joafaust          #+#    #+#             */
/*   Updated: 2025/03/26 14:29:14 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"
#include <string.h>

void	print_action(t_simulation *sim, int id, char *action)
{
	pthread_mutex_lock(&sim->print_lock);
	pthread_mutex_lock(&sim->death_check);
	if (!sim->stop)
	{
		pthread_mutex_unlock(&sim->death_check);
		if (ft_strcmp(action, "has taken a fork") == 0)
			printf(MSG_FORK, get_time_in_ms() - sim->start_time, id);
		else if (ft_strcmp(action, "is eating") == 0)
			printf(MSG_EATING, get_time_in_ms() - sim->start_time, id);
		else if (ft_strcmp(action, "is sleeping") == 0)
			printf(MSG_SLEEPING, get_time_in_ms() - sim->start_time, id);
		else if (ft_strcmp(action, "is thinking") == 0)
			printf(MSG_THINKING, get_time_in_ms() - sim->start_time, id);
		else if (ft_strcmp(action, "died") == 0)
			printf(MSG_DEAD, get_time_in_ms() - sim->start_time, id);
		pthread_mutex_unlock(&sim->print_lock);
		return ;
	}
	pthread_mutex_unlock(&sim->death_check);
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
	while (1)
	{
		pthread_mutex_lock(&philo->sim->death_check);
		if (philo->sim->stop)
		{
			pthread_mutex_unlock(&philo->sim->death_check);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->sim->death_check);
		usleep(100);
		eat(philo);
		if (has_eaten_enough(philo))
			return (NULL);
		sleep_philo(philo);
		think(philo);
	}
}

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	while (!sim->stop)
	{
		check_deaths(sim);
		pthread_mutex_lock(&sim->death_check);
		if (sim->stop) // Exit if someone died
		{
			pthread_mutex_unlock(&sim->death_check);
			return (NULL);
		}
		pthread_mutex_unlock(&sim->death_check);
		check_all_eaten(sim);
		usleep(100);
	}
	return (NULL);
}
