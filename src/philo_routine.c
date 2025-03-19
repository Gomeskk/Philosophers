/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:31:47 by joafaust          #+#    #+#             */
/*   Updated: 2025/03/19 13:11:38 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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
	while (!philo->sim->stop)
	{
		print_action(philo->sim, philo->id, "is thinking");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo->sim, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo->sim, philo->id, "has taken a fork");
		print_action(philo->sim, philo->id, "is eating");
		philo->last_meal_time = get_time_in_ms();
		usleep(philo->sim->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		philo->meals_eaten++;
		if (philo->sim->must_eat_count > 0
			&& philo->meals_eaten >= philo->sim->must_eat_count)
			break ;
		print_action(philo->sim, philo->id, "is sleeping");
		usleep(philo->sim->time_to_sleep * 1000); //fazer uma função para sleep em si e não usar o usleep, cena de deadlock
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
