/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:31:47 by joafaust          #+#    #+#             */
/*   Updated: 2025/03/20 16:05:59 by joafaust         ###   ########.fr       */
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
	while (!philo->sim->stop)
	{
		think(philo);
		eat(philo);
		if (has_eaten_enough(philo))
			break ;
		sleep_philo(philo);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;
	int				i;

	sim = (t_simulation *)arg;
	i = 0;
	while (!sim->stop)
	{
		if (get_time_in_ms()
			- sim->philos[i].last_meal_time >= sim->time_to_die)
		{
			print_action(sim, sim->philos[i].id, "died");
			sim->stop = 1;
			return (NULL);
		}
		i++;
		if (i >= sim->num_philos)
			i = 0;
		usleep(1000);
	}
	return (NULL);
}
