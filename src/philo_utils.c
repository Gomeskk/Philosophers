/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:40:51 by joafaust          #+#    #+#             */
/*   Updated: 2025/03/25 00:29:43 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	think(t_philo *philo)
{
	print_action(philo->sim, philo->id, "is thinking");
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0) // even philosopher
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo->sim, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
	}
	else // odd philosopher
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo->sim, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
	}
	print_action(philo->sim, philo->id, "has taken a fork");
	print_action(philo->sim, philo->id, "is eating");
	pthread_mutex_lock(&philo->sim->meal_check);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->sim->meal_check);
	ft_usleep(philo->sim->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&philo->sim->meal_check);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->sim->meal_check);
}

void	sleep_philo(t_philo *philo)
{
	print_action(philo->sim, philo->id, "is sleeping");
	ft_usleep(philo->sim->time_to_sleep);
}

int	has_eaten_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->meal_check);
	if (philo->sim->must_eat_count > 0
		&& philo->meals_eaten >= philo->sim->must_eat_count)
		{
			pthread_mutex_unlock(&philo->sim->meal_check);
			return (1);
		}
	pthread_mutex_unlock(&philo->sim->meal_check);
	return (0);
}

void	handle_one_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo->sim, philo->id, "has taken a fork");
	ft_usleep(philo->sim->time_to_die);
	print_action(philo->sim, philo->id, "died");
	pthread_mutex_unlock(philo->left_fork);
	philo->sim->stop = 1;
}
