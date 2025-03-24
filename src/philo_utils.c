/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:40:51 by joafaust          #+#    #+#             */
/*   Updated: 2025/03/24 14:29:56 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	think(t_philo *philo)
{
	print_action(philo->sim, philo->id, "is thinking");
}

void	eat(t_philo *philo)
{
	//wait_for_turn(philo);
	pthread_mutex_lock(philo->left_fork);
	print_action(philo->sim, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo->sim, philo->id, "has taken a fork");
	print_action(philo->sim, philo->id, "is eating");
	philo->last_meal_time = get_time_in_ms();
	ft_usleep(philo->sim->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->meals_eaten++;
	//switch_turn(philo);
}

void	sleep_philo(t_philo *philo)
{
	print_action(philo->sim, philo->id, "is sleeping");
	ft_usleep(philo->sim->time_to_sleep);
}

int	has_eaten_enough(t_philo *philo)
{
	if (philo->sim->must_eat_count > 0
		&& philo->meals_eaten >= philo->sim->must_eat_count)
		return (1);
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
